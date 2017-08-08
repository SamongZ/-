#include <pthread.h>
#include <semaphore.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#define CUSTOMER_NUM 10
/* ĳӪҵ��ֻ��ͬʱ���������˿�
 * �ж���˿�ͬʱ���������ַ��񴰿���������ȴ�
 * ����д��ڿ��У�����ܷ���
 */
sem_t sem;

void* get_service(void *thread_id)
{
    int customer_id = *(int*)thread_id;
    if (sem_wait(&sem) == 0)  // ���óɹ���sem > 0��������sem��1
    {
        Sleep(1000);
        printf("customer %d receive service...\n", customer_id);
        sem_post(&sem);  // ������ɣ�sem��1
    }
}
int main()
{
    sem_init(&sem, 0, 2);
    pthread_t customer[CUSTOMER_NUM];
    int i, iRet;
    /* Ϊÿһ���˿�����һ���߳� */
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
    /* �ȴ����й˿͵��߳̽��� */
    int j;
    for (j =0; j < CUSTOMER_NUM; ++j)
        pthread_join(customer[j], nullptr);
    /* �����ź��� */
    sem_destroy(&sem);
    return 0;
}
