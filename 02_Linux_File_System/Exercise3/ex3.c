#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if ((argc != 4) && (argc != 5))
    {
        printf("Usage: %s filename num-bytes [r/w] \"Hello\"\n", argv[0]);
        return 0;
    }

    int fd;
    char *path = argv[1];
    int num_bytes = atoi(argv[2]);
    char mode = argv[3][0];

    switch (mode)
    {
    case 'r':
    {
        fd = open(path, O_RDONLY);
        if (-1 == fd)
        {
            printf("Error: Cannot open file\n");
            close(fd);
            return -1;
        }

        char *buf;
        int num_bytes_read = read(fd, buf, num_bytes);

        if (num_bytes_read == -1)
        {
            printf("Error: Cannot read\n");
            close(fd);
            return -1;
        }
        buf[num_bytes_read] = '\0';

        printf("%s\n", buf);
        break;
    }
    case 'w':
    {
        fd = open(path, O_WRONLY);
        if (-1 == fd)
        {
            printf("Error: Cannot open file\n");
            close(fd);
            return -1;
        }

        char *data = argv[4];
        if (-1 == write(fd, data, strlen(data)))
        {
            printf("Error: Cannot write\n");
            close(fd);
            return -1;
        }

        break;
    }
    default:
        printf("Error: Invalid mode. Use 'r' for read or 'w' for write.\n");
        return -1;
    }
    return 0;
}