#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }

    int fd;
    fd = open(argv[1], O_RDWR | O_APPEND); // file offset is set to the end of file
    /* When a file is opened with the O_APPEND flag, all write operations automatically append data to the end of the file,
    regardless of the current file offset*/

    if (-1 == fd)
    {
        printf("Can not open file %s\n", argv[1]);
        return -1;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) // file offset is set to start of file
    {
        printf("Seek failed\n");
        close(fd);
        return -1;
    }

    // Because fd is open with O_APPEND, file offset is always automatically set to end
    // of file when using write function
    if (write(fd, "AAAA", strlen("AAAA")) == -1)
    {
        printf("Write error");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}