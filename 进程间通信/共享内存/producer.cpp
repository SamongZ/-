#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include "shm_com.h"
#define SIZE 2048
int main()
{
    int shmid;
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed.\n");
        exit(EXIT_FAILURE);
    }
    void *shared_memory = (void*)0;
    shared_memory = shmat(shmid, (void*)0, 0);
    if (shared_memory == (void*)-1) {
        fprintf(stderr, "shmat failed.\n");
        exit(EXIT_FAILURE);
    }
    struct shared_use_st *shared_stuff;
    shared_stuff = (struct shared_use_st*)shared_memory;
    char buffer[SIZE];
    while (1) {
        while (shared_stuff -> written == 1) {
            printf("waiting for client...\n");
            sleep(1);
        }
        printf("input data: ");
        fgets(buffer, SIZE, stdin);
        strcpy(shared_stuff -> text, buffer);
        shared_stuff -> written = 1;
        if (strncmp(buffer, "end", 3) == 0)
                break;
    }
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
