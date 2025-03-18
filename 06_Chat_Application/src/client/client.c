#include "client.h"

static void thread_serv_handler(void *arg)
{
    pthread_detach(pthread_self());
    connection_data_t serv_data = *((connection_data_t *)arg);

    pthread_mutex_lock(&mutex);
    add_connection_data(&serv_data);
    // Notify that a new connection has been added
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    receiving_message(&serv_data);
}

void connect_to_server(char ip[], in_port_t port)
{
    if (is_valid_server(ip, port) == -1)
    {
        return;
    }

    struct sockaddr_in servaddr;
    connection_data_t serv_data;

    // Initialize servaddr and serv_data
    bzero(&servaddr, sizeof(servaddr));
    bzero(&serv_data, sizeof(serv_data));

    // Store the server connection information
    strcpy(serv_data.ip_address, inet_ntoa(servaddr.sin_addr));
    serv_data.sockfd = create_socket();
    serv_data.port = port;

    // Set the server connection information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);

    if (connect_to_socket(serv_data.sockfd, &servaddr) == -1)
    {
        return;
    }

    // Get the port number of application
    char port_str[6];
    bzero(port_str, sizeof(port_str));
    snprintf(port_str, sizeof(port_str), "%d", APP_PORT);

    // Send the application port number to the server
    write(serv_data.sockfd, port_str, sizeof(port_str));

    // Create a thread to handle the server connection
    pthread_create(&serv_data.thread_id, NULL, (void *)&thread_serv_handler, (void *)&serv_data);

    // Wait for the thread to be added to the connection list
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

int is_valid_server(char ip[], in_port_t port)
{
    // Check if the IP address is valid
    struct sockaddr_in servaddr;
    if (inet_pton(AF_INET, ip, &servaddr) <= 0)
    {
        printf("\nInvalid IP address: %s\n", ip);
        return -1;
    }

    char local_ip_address[INET_ADDRSTRLEN];
    get_local_ip_address(local_ip_address, INET_ADDRSTRLEN);

    // Check if the application is trying to connect to itself
    if (strcmp(ip, local_ip_address) == 0 && port == APP_PORT)
    {
        printf("\nCannot connect to yourself.\n");
        return -1;
    }

    // Check if the port is valid
    if (port < 1024 || port > 65535)
    {
        printf("\nInvalid port number: %d\n", port);
        return -1;
    }

    // Check if server is already connected
    for (int i = 0; i < nconn; i++)
    {
        if (strcmp(ip, conn_data[i].ip_address) == 0 && port == conn_data[i].port)
        {
            printf("\nAlready connected to %s on port %d\n", ip, port);
            return -1;
        }
    }

    return 0;
}