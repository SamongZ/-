#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd[2]; // 管道两端，fd[0]为读端，fd[1]为写端
    pid_t pid;
    char buf[256];
    int return_cnt;
    /* 创建管道 */
    pipe(fd);
    /* 创建子进程 */
    pid = fork();
    if (pid < 0) {
        printf("Error in fork.\n");
        exit(1);
    }
    else if (pid == 0) {
        printf("in child process...\n");
        /* 子进程从管道写数据， 关闭管道的读端 */
        close(fd[0]);
        write(fd[1], "hello world", strlen("hello world"));
        exit(0);
    }
    else {
        printf("in parent process...\n");
        /* 父进程从管道读数据， 关闭管道的写端 */
        close(fd[1]);
		bzero(buf, sizeof(buf));
        return_cnt = read(fd[0], buf, sizeof(buf));
        printf("%d byes of data received from child process: %s\n", return_cnt, buf);
    }
    return 0;
}
