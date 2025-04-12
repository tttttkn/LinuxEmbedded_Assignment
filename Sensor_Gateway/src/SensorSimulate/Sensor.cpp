#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../SharedData/SharedData.hpp"

#define SERVER_PORT 8000
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Specify the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.23"); // Server IP address (localhost)

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server.\n");

    while (1)
    {
        sleep(10);
        // Send a message to the server
        SensorData sensorData;
        sensorData.sensorId = 4000;
        sensorData.sensorTemp = rand() % 51; // Generate a random number between 0 and 50
        sensorData.timestamp = 1625256000;   // Example timestamp
        if (write(sockfd, &sensorData, sizeof(sensorData)) == -1)
        {
            perror("Failed to send data");
            break;
        }
        printf("Sensor data sent: ID=%d, Temp=%d, Timestamp=%d\n", sensorData.sensorId, sensorData.sensorTemp, sensorData.timestamp);
    }

    // Close the socket
    close(sockfd);
    printf("Disconnected from the server.\n");

    return 0;
}
