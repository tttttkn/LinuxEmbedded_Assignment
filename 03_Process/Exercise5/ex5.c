/*BT5. Tạo Process Zombie và Orphan
1. Mô tả: Viết một chương trình tạo ra một tiến trình zombie và một tiến trình orphan để hiểu
          về các loại tiến trình đặc biệt này.
2. Yêu cầu:
    - Để tạo zombie, cho tiến trình cha kết thúc sớm trong khi tiến trình con vẫn còn chạy,
      và sử dụng ps để quan sát trạng thái zombie của tiến trình.
    - Để tạo orphan, cho tiến trình con ngủ trong một khoảng thời gian dài hơn tiến trình cha,
      để tiến trình con trở thành orphan.
    - Giải thích trạng thái zombie và orphan, cùng lý do tại sao chúng xuất hiện trong Linux.

*/


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void createZombie()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child process (Zombie) PID: %d\n", getpid());
        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process (Zombie creator) PID: %d\n", getpid());
        while(1);
    }
    else
    {
        printf("Fork failed\n");
    }
}

void createOrphan()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child process (Orphan) PID: %d, Parent PID: %d\nRemember to kill Orphan process\n", getpid(), getppid());
        while (1);
        
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process (Orphan creator) PID: %d\n", getpid());
    }
    else
    {
        printf("Fork failed\n");
    }
}

int main()
{
    // printf("Creating a zombie process...\n");
    // createZombie();

    printf("Creating an orphan process...\n");
    createOrphan();



    return 0;
}