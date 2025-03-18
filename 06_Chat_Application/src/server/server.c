#include "server.h"

in_port_t APP_PORT = 0;

int is_server_listening = 0;

static int sockfd = 0;

pthread_t server_thread = 0;

pthread_mutex_t server_started_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t server_started_cond = PTHREAD_COND_INITIALIZER;

void *server_start_listening()
{
    setup_server_socket();

    struct sockaddr_in cli;
    while (1)
    {
        int connfd = accept_client_connection(&cli);
        if (connfd < 0)
        {
            perror("\nServer acccept failed");
            continue;
        }

        handle_client_connection(connfd, &cli);
    }
}

void setup_server_socket()
{
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(APP_PORT);

    pthread_mutex_lock(&server_started_mutex);
    if (listening_socket(sockfd, &servaddr, MAXNCLI) != -1 && sockfd != -1)
    {
        is_server_listening = 1;
        printf("\nServer started listening on port %d\n", APP_PORT);
    }
    else
    {
        close_server();
    }
    // Notify that the server is listening, main thread can continue with command handler
    pthread_cond_signal(&server_started_cond);
    pthread_mutex_unlock(&server_started_mutex);
}

int accept_client_connection(struct sockaddr_in *cli)
{
    unsigned int len = sizeof(*cli);

    int connfd = accept(sockfd, (SA *)cli, &len);
    if (connfd < 0)
    {
        perror("\nServer accept failed");
    }
    else
    {
        printf("\nConnected with %s on port %d\n", inet_ntoa(cli->sin_addr), APP_PORT);
    }

    return connfd;
}

void handle_client_connection(int connfd, struct sockaddr_in *cli)
{
    // Create a connection data object to store the client connection information
    connection_data_t cli_data;
    cli_data.sockfd = connfd;
    strcpy(cli_data.ip_address, inet_ntoa(cli->sin_addr));

    // Get the port number of the client application
    char port_str[6];
    read(connfd, port_str, sizeof(port_str));
    cli_data.port = atoi(port_str);

    // Create a thread to handle the client connection
    pthread_create(&cli_data.thread_id, NULL, (void *)&thread_cli_handler, &cli_data);

    // Wait for the thread to be added to the connection list
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void thread_cli_handler(void *arg)
{
    pthread_detach(pthread_self());

    connection_data_t cli_data = *((connection_data_t *)arg);

    pthread_mutex_lock(&mutex);

    add_connection_data(&cli_data);

    // Notify that a new connection has been added
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    receiving_message(&cli_data);
}

void print_app_port()
{
    printf("\nYour port: %d\n", APP_PORT);
}

void print_server_ip()
{
    char buffer[INET_ADDRSTRLEN];
    get_local_ip_address(buffer, INET_ADDRSTRLEN);
    printf("\nYour IP address: %s\n", buffer);
}

void close_server()
{
    terminate_all_connections();
    close(sockfd);
    is_server_listening = 0;
    pthread_cancel(server_thread);
}
