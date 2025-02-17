/*BT2. Sử dụng exec và Biến Môi Trường
- Mô tả: Viết một chương trình trong đó tiến trình con sẽ thay thế chương trình đang chạy
bằng một chương trình khác, ví dụ ls hoặc date, sử dụng hàm execlp() hoặc execvp().
- Yêu cầu:
Truyền các biến môi trường vào chương trình và thực hiện các công việc khác nhau 
(ví dụ biến môi trường được truyền vào là 1 thì thực hiện lệnh ls, nếu là 2 thì thực hiện lệnh date).
Giải thích điều gì xảy ra với tiến trình ban đầu sau khi exec được gọi.
*/


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc , char *argv[])
{

    if ((argc != 2) || ((atoi(argv[1]) != 1) && (atoi(argv[1]) != 2)))
    {
        printf("Usage: %s [1/2]\n", argv[0]);
        return -1;
    }

    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        if (atoi(argv[1]) == 1)
        {
            execlp("ls", "ls", NULL);
        }
        else if (atoi(argv[1]) == 2)
        {
            execlp("date", "date", NULL);
        }
        else 
        {
            printf("Usage: %s [1/2]\n", argv[0]);
            return -1;
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        printf("Error\n");
    }
    
    return 0;

}