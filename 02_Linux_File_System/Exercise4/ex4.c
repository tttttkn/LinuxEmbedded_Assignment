
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct stat sb;
    if (stat(argv[1], &sb) == -1)
    {
        printf("Usage: %s file_name\n", argv[0]);
        return -1;
    }

    printf("File type:              ");

    switch (sb.st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFLNK:
        printf("symbolic (soft) link\n");
        break;
    case S_IFIFO:
        printf("FIFO or pipe\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown file type?\n");
        break;
    }

    printf("File name:              %s\n", argv[1]);
    printf("Last file modification: %s", ctime(&sb.st_mtime));
    printf("File size:              %ld\n", (long)sb.st_size);

    return 0;
}