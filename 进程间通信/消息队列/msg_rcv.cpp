#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#define MAXSIZE 256

struct msg_st
{
    long int msg_type;
    char text[MAXSIZE];
};

int main()
{
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0;
    /* 建立消息队列 */
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    /* 在消息队列中读取数据，遇到end停止 */
    while (1) {
        if (msgrcv(msgid, (void*)&data, MAXSIZE, msgtype, 0) == -1) {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("receive data: %s\n", data.text);
        if (strncmp(data.text, "end", 3) == 0)
            break;
    }
    /* 删除消息队列 */
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
