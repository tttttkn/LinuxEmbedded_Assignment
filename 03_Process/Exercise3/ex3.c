/*BT3. Tín hiệu Process
- Mô tả: Viết một chương trình tạo hai process cha - con. Tiến trình cha sẽ gửi tín hiệu SIGUSR1 tới tiến trình con 
sau một khoảng thời gian.
- Yêu cầu:
Sử dụng signal() để định nghĩa hành vi của tiến trình con khi nhận tín hiệu SIGUSR1.
In ra một thông báo khi tiến trình con nhận được tín hiệu.

*/


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>


void signalHandler(int sig)
{
    printf("Child process received signal SIGUSR1\n");
    exit(EXIT_SUCCESS);
}

void waitHandler(int sig)
{
    wait(NULL);
}

int main(int argc , char *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        signal(SIGUSR1, signalHandler);
        while(1);
    }
    else if (pid > 0)
    {
        printf("Parent process send signal SIGUSR1 to child process after 5 seconds\n");
        sleep(5);
        kill(pid, SIGUSR1); // Send SIGUSR1 to the child process
        signal(SIGCHLD, waitHandler);
    }
    else
    {
        printf("Error\n");
    }
    
    return 0;

}