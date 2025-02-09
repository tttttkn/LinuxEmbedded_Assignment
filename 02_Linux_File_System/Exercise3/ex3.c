/*BT3. Viết một chương trình có só lượng command-line arguments là 3, có dạng như sau:
$ ./example_program filename num-bytes [r/w] "Hello"
Trong đó:
	1. example_grogram: Tên file thực thi
	2. filename: Tên file
	3. num-bytes: Số byte muốn read/write
	4. [r/w]: r -> Thực hiện đọc từ  filename và in ra màn hình
		    w -> Thực hiện ghi vào filename
	5. "Hello": Nội dung bất kì muốn read/write vào filename*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if((argc != 4) && (argc != 5))
    {
        printf("Usage: %s filename num-bytes [r/w] \"Hello\"\n",argv[0]);
        return 0;
    }

    int fd;
    char* path = argv[1];
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
            char* data = argv[4];
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
        break;
    }
    return 0;
}