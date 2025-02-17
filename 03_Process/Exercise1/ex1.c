/*BT1. Khởi tạo và Theo dõi Process
Mô tả: Viết một chương trình C tạo một process con bằng cách sử dụng fork(). Sau khi tạo process, 
tiến trình con sẽ in ra PID của nó và tiến trình cha in ra PID của tiến trình con.*/




#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        printf("I am Child process, myPID: %d\n", getpid());
    }
    else if (pid > 0)
    {
        printf("I am Parent process, childPID: %d\n",pid);
        wait(NULL);
    }
    else
    {
        printf("Error\n");
    }
    
    return 0;

}