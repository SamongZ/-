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
	char buffer[MAXSIZE];

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    while (1) {
        printf("input the data: ");
		fgets(buffer, MAXSIZE, stdin);
        data.msg_type = 1;
		strcpy(data.text, buffer);

        if (msgsnd(msgid, (void*)&data, MAXSIZE, 0) == -1) {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "end", 3) == 0)
            break;
    }
    return 0;
}
