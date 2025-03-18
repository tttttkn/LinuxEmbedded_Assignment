#include "connection_handler.h"

connection_data_t conn_data[MAXCONN];
int nconn = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void send_message(int conn_id, const char *msg)
{
    if (strlen(msg) > MAX_MSG_LEN)
    {
        printf("\nLength of message exceed %d: %ld\n", MAX_MSG_LEN, strlen(msg));
    }
    else if (write(conn_data[conn_id].sockfd, msg, strlen(msg)) == -1)
    {
        perror("\nCan not send message");
    }
    else
    {
        printf("\nMessage sent successfully\n");
    }
}

void add_connection_data(const connection_data_t *connection_data)
{
    // Add the connection data to the connection list
    conn_data[nconn] = *connection_data;

    nconn++;
}

void receiving_message(const connection_data_t *sender_data)
{

    char buf[MAX_MSG_LEN];
    int num_read;

    while (1)
    {
        bzero(buf, MAX_MSG_LEN);

        num_read = read(sender_data->sockfd, buf, MAX_MSG_LEN);
        if (num_read == 0)
        {
            printf("\nLost connection with %s on port %d\n", sender_data->ip_address, sender_data->port);

            pthread_mutex_lock(&mutex);
            int connection_id = find_conn_id_by_sockfd(sender_data->sockfd);
            terminate_connection(connection_id);
            pthread_mutex_unlock(&mutex);
        }
        else if (num_read > 0)
        {
            print_message(buf, sender_data->ip_address, sender_data->port);
        }
        else
        {
            perror("\nRead error");
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
    for (i = 0; i < nconn; i++)
    {
        if (conn_data[i].sockfd == sockfd)
        {
            break;
        }
    }

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

void print_message(const char *message, const char *sender_ip_address, in_port_t sender_port)
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
