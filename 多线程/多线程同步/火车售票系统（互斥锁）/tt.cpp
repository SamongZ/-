#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

int total_ticket_num = 20;
pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER;
void* sell_ticket(void *arg) {
    for (int i = 0; i < 20; ++i) {
        pthread_mutex_lock(&mutex_x);  // mutex_lock 与 mutex_unlock之间构成原子操作
        if (total_ticket_num > 0) {
            Sleep(100);
            printf("sell the %dth ticket\n", 20 - total_ticket_num + 1);
            total_ticket_num--;
        }
        pthread_mutex_unlock(&mutex_x);
    }
    return 0;
}
int main()
{
    int iRet;
    pthread_t tids[4];
    for (int i = 0; i < 4; ++i) {
        iRet = pthread_create(&tids[i], nullptr, sell_ticket, nullptr);
        if (iRet) {
            printf("pthread_create error, iRet = %d\n", iRet);
            return iRet;
        }
    }
    Sleep(2500);
    void *retval;
    for (int i = 0; i < 4; ++i) {
        iRet = pthread_join(tids[i], &retval);
        if (iRet) {
            printf("tid = %d join error, iRet = %d\n", tids[i], iRet);
            return iRet;
        }
        printf("retval = %ld\n", (long*)retval);
    }
    return 0;
}
