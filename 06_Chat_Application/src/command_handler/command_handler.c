

#include "command_handler.h"

pthread_t command_handler_thread = 0;

void command_handler()
{
    char command_input[MAX_INPUT_SIZE];

    while (is_server_listening)
    {
        bzero(command_input, MAX_INPUT_SIZE);
        get_input_from_user(command_input);
        command_parser(command_input);
    }
}

void get_input_from_user(char *buff)
{
    printf("\nEnter a command: ");
    fgets(buff, MAX_INPUT_SIZE, stdin);
    buff[strlen(buff) - 1] = '\0';
}

void command_parser(char *command_input)
{
    char *command = strtok(command_input, " ");

    if (command == NULL)
    {
        printf("\nInvalid command\n");
        return;
    }

    if (strcmp(command, "connect") == 0)
    {
        char *ip_address = strtok(NULL, " ");
        char *port = strtok(NULL, "");

        if (ip_address && port)
        {
            connect_to_server(ip_address, atoi(port));
        }
        else
        {
            printf("\nInvalid command\n");
        }
    }
    else if (strcmp(command, "send") == 0)
    {
        char *conn_id_str = strtok(NULL, " ");
        char *msg = strtok(NULL, "");

        if (conn_id_str && msg)
        {
            send_message(atoi(conn_id_str), msg);
        }
        else
        {
            printf("\nInvalid command\n");
        }
    }
    else if (strcmp(command, "list") == 0 && strtok(NULL, " ") == NULL)
    {
        print_list_connections(conn_data, nconn);
    }
    else if (strcmp(command, "help") == 0 && strtok(NULL, " ") == NULL)
    {
        print_help();
    }
    else if (strcmp(command, "myip") == 0 && strtok(NULL, " ") == NULL)
    {
        print_server_ip();
    }
    else if (strcmp(command, "myport") == 0 && strtok(NULL, " ") == NULL)
    {
        print_app_port();
    }
    else if (strcmp(command, "terminate") == 0)
    {
        char *conn_id_str = strtok(NULL, " ");
        if (conn_id_str && strtok(NULL, " ") == NULL)
        {
            terminate_connection(atoi(conn_id_str));
        }
        else
        {
            printf("\nInvalid command\n");
        }
    }
    else if (strcmp(command, "exit") == 0 && strtok(NULL, " ") == NULL)
    {
        close_server();
        printf("\nApplication is exiting\n");
    }
    else
    {
        printf("\nInvalid command\n");
    }
}

void print_help()
{
    printf("\n*********************** CHAT APPLICATION **********************\n");
    printf("Use the commands below:\n");
    printf("1. help\t\t\t\t\t: Display user interface options\n");
    printf("2. myip\t\t\t\t\t: Display IP address of this server\n");
    printf("3. myport\t\t\t\t: Display listening port of this app\n");
    printf("4. connect <destination> <port no>\t: Connect to another computer\n");
    printf("5. list\t\t\t\t\t: List all the current connections of this computer\n");
    printf("6. terminate <connection id>\t\t: Terminate the connection\n");
    printf("7. send <connection id> <message>\t: Send a message to the connection\n");
    printf("8. exit\t\t\t\t\t: Close all connections and terminate this app\n");
    printf("***************************************************************\n");
}
