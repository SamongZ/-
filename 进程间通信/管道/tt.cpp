#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd[2]; // �ܵ����ˣ�fd[0]Ϊ���ˣ�fd[1]Ϊд��
    pid_t pid;
    char buf[256];
    int return_cnt;
    /* �����ܵ� */
    pipe(fd);
    /* �����ӽ��� */
    pid = fork();
    if (pid < 0) {
        printf("Error in fork.\n");
        exit(1);
    }
    else if (pid == 0) {
        printf("in child process...\n");
        /* �ӽ��̴ӹܵ�д���ݣ� �رչܵ��Ķ��� */
        close(fd[0]);
        write(fd[1], "hello world", strlen("hello world"));
        exit(0);
    }
    else {
        printf("in parent process...\n");
        /* �����̴ӹܵ������ݣ� �رչܵ���д�� */
        close(fd[1]);
		bzero(buf, sizeof(buf));
        return_cnt = read(fd[0], buf, sizeof(buf));
        printf("%d byes of data received from child process: %s\n", return_cnt, buf);
    }
    return 0;
}
