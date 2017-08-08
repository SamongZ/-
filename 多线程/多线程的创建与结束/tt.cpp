#include <stdio.h>
#include <pthread.h>
#include <windows.h>

void* say_hello(void *args) {
    /* �̵߳����к���������void*��û˵�ı�ʶ����ͨ��ָ�롢����ͨ��ָ�� */
    Sleep(5000);
    int i = *(int*)args;
    printf("hello from thread, i = %d\n", i);
    printf("thread id in pthread = %lu\n", pthread_self());   // �õ��߳�id
    pthread_exit((void*)1);  // �߳̽���������1
}
int main()
{
    pthread_t tid;
    int para = 100;
    int iRet = pthread_create(&tid, nullptr, say_hello, &para);
    /* ��������Ϊ���߳�id���̲߳��������ú�����������ĺ������� */
    /* �̴߳����ɹ�ʱ������ֵiRetΪ0 */
    if (iRet) {
        printf("pthread_create error: iRet = %d\n", iRet);
        return iRet;
    }
    printf("thread id in pthread = %lu\n", tid);  // ��һ�ַ����õ��߳�id
    void *retval;
    iRet = pthread_join(tid, &retval);  // �ȴ��߳̽���
    if (iRet) {
        printf("pthread_join error: iRet = %d\n", iRet);
        return iRet;
    }
    printf("retval = %ld\n", (long)retval);
    return 0;
}
