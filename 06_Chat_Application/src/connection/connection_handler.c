#include "connection_handler.h"

connection_data_t conn_data[MAXCONN];
int nconn = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void send_message(int conn_id, char *msg)
{
    if (strlen(msg) > 100)
    {
        printf("\nLength of message exceed 100: %ld\n", strlen(msg));
    }
    else if (write(conn_data[conn_id].sockfd, msg, strlen(msg)) == -1)
    {
        printf("\nCan not send message\n");
    }
    else
    {
        printf("\nMessage sent successfully\n");
    }
}

void add_connection_data(char ip_address[], in_port_t port, int sockfd, pthread_t thread_id)
{

    // Add the connection data to the connection list
    strcpy(conn_data[nconn].ip_address, ip_address);
    conn_data[nconn].port = port;
    conn_data[nconn].sockfd = sockfd;
    conn_data[nconn].thread_id = thread_id;

    nconn++;
}

void receiving_message(connection_data_t *sender_data)
{
    int nfds = sender_data->sockfd + 1;
    fd_set readfds;
    char buf[1024];
    while (1)
    {
        FD_ZERO(&readfds);

        FD_SET(sender_data->sockfd, &readfds);

        select(nfds, &readfds, NULL, NULL, NULL);

        bzero(buf, 1024);

        int connection_id = find_conn_id_by_sockfd(sender_data->sockfd);

        int num_read = read(sender_data->sockfd, buf, 1024);
        if (num_read == 0)
        {
            printf("\nLost connection with %s on port %d\n", conn_data[connection_id].ip_address, conn_data[connection_id].port);

            pthread_mutex_lock(&mutex);
            terminate_connection(connection_id);
            pthread_mutex_unlock(&mutex);
        }
        else if (num_read > 0)
        {
            print_message(buf, sender_data->ip_address, sender_data->port);
        }
        else
        {
            printf("\nRead error\n");
        }
    }
}

void terminate_connection(int conn_id)
{
    if (close(conn_data[conn_id].sockfd) == -1)
    {
    }
    else
    {
        pthread_cancel(conn_data[conn_id].thread_id);
        remove_connection_from_list(conn_id);
    }
}

void remove_connection_from_list(int conn_id)
{
    for (int i = conn_id; i < nconn - 1; i++)
    {
        conn_data[i] = conn_data[i + 1];
    }
    nconn--;
}

int find_conn_id_by_sockfd(int sockfd)
{
    int i = 0;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < nconn; i++)
    {
        if (conn_data[i].sockfd == sockfd)
        {
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    return i;
}

void terminate_all_connections()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < nconn; i++)
    {
        terminate_connection(i);
    }
    pthread_mutex_unlock(&mutex);
}

void print_message(char *message, char sender_ip_address[], in_port_t sender_port)
{
    printf("\n****************************************\n");
    printf("Message received from %s\n", sender_ip_address);
    printf("Sender’s Port: %d\n", sender_port);
    printf("Message: \"%s\"\n", message);
    printf("****************************************\n");
}

void print_list_connections(const connection_data_t connection_data[], const int nconnection)
{
    printf("\nID\t|\tIP Address\t|\tPort\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < nconnection; i++)
    {
        printf("%d\t|\t%s\t|\t%d\n", i, connection_data[i].ip_address, connection_data[i].port);
    }
}
