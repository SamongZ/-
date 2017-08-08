#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <iostream>
#include <windows.h>
using namespace std;

/* 提示出租车到达的条件变量 */
pthread_cond_t taxiCond = PTHREAD_COND_INITIALIZER;
/* 同步锁 */
pthread_mutex_t taxiMutex = PTHREAD_MUTEX_INITIALIZER;
/* 到达乘客的数量 */
int travelerNumber = 0;

void* travelerArrive(void* name) {
    cout << "Traveler: " << (char*)name << " needs a taxi now!" << endl;
    pthread_mutex_lock(&taxiMutex);
    ++travelerNumber;
    pthread_cond_wait(&taxiCond, &taxiMutex);
    cout << "Traveler: " << (char*)name << " now got a taxi!" << endl;
    pthread_mutex_unlock(&taxiMutex);
    pthread_exit((void*)0);
}

void* taxiArrive(void* name) {
    cout << "Taxi: " << (char*)name << " arrives" << endl;
    while (1) {
        pthread_mutex_lock(&taxiMutex);
        if (travelerNumber > 0) {
            pthread_cond_signal(&taxiCond);
            pthread_mutex_unlock(&taxiMutex);
            break;
        }
        pthread_mutex_unlock(&taxiMutex);
    }
    pthread_exit((void*)0);
}

int main()
{
    pthread_t tids[4];

    int iRet = pthread_create(&tids[0], nullptr, taxiArrive, (void*)("Jack"));
    if (iRet) {
        printf("pthread_create error: iRet = %d\n", iRet);
        return iRet;
    }
    Sleep(1000);

    iRet = pthread_create(&tids[1], nullptr, travelerArrive, (void*)("Samong"));
    if (iRet) {
        printf("pthread_create error: iRet = %d\n", iRet);
        return iRet;
    }
    Sleep(1000);

    iRet = pthread_create(&tids[2], nullptr, travelerArrive, (void*)("Jim"));
    if (iRet) {
        printf("pthread_create error: iRet = %d\n", iRet);
        return iRet;
    }
    Sleep(1000);

    iRet = pthread_create(&tids[3], nullptr, taxiArrive, (void*)("Kobe"));
    if (iRet) {
        printf("pthread_create error: iRet = %d\n", iRet);
        return iRet;
    }
    Sleep(1000);

    void* retval;
    for (int j = 0; j < 4; ++j) {
        iRet = pthread_join(tids[j], &retval);
        if (iRet) {
            printf("pthread_join error: iRet = %d\n", iRet);
            return iRet;
        }
        printf("retval = %ld\n", (long)retval);
    }
    return 0;
}
