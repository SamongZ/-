#include <pthread.h>
#include <semaphore.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#define CUSTOMER_NUM 10
/* 某营业厅只能同时服务两个顾客
 * 有多个顾客同时到达，如果发现服务窗口已满，则等待
 * 如果有窗口空闲，则接受服务
 */
sem_t sem;

void* get_service(void *thread_id)
{
    int customer_id = *(int*)thread_id;
    if (sem_wait(&sem) == 0)  // 调用成功（sem > 0），并且sem减1
    {
        Sleep(1000);
        printf("customer %d receive service...\n", customer_id);
        sem_post(&sem);  // 服务完成，sem加1
    }
}
int main()
{
    sem_init(&sem, 0, 2);
    pthread_t customer[CUSTOMER_NUM];
    int i, iRet;
    /* 为每一个顾客生成一个线程 */
    for (i = 0; i < CUSTOMER_NUM; ++i) {
        int customer_id = i;
        iRet = pthread_create(&customer[i], nullptr, &get_service, &customer_id);
        if (iRet) {
            perror("pthread_creat");
            return iRet;
        }
        else {
            printf("customer %d arrived.\n", customer_id);
        }
        Sleep(500);
    }
    /* 等待所有顾客的线程结束 */
    int j;
    for (j =0; j < CUSTOMER_NUM; ++j)
        pthread_join(customer[j], nullptr);
    /* 销毁信号量 */
    sem_destroy(&sem);
    return 0;
}
