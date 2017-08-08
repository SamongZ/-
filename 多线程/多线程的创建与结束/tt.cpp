#include <stdio.h>
#include <pthread.h>
#include <windows.h>

void* say_hello(void *args) {
    /* 线程的运行函数，必须void*，没说的标识返回通用指针、输入通用指针 */
    Sleep(5000);
    int i = *(int*)args;
    printf("hello from thread, i = %d\n", i);
    printf("thread id in pthread = %lu\n", pthread_self());   // 得到线程id
    pthread_exit((void*)1);  // 线程结束，返回1
}
int main()
{
    pthread_t tid;
    int para = 100;
    int iRet = pthread_create(&tid, nullptr, say_hello, &para);
    /* 参数依次为：线程id、线程参数、调用函数名、传入的函数参数 */
    /* 线程创建成功时，返回值iRet为0 */
    if (iRet) {
        printf("pthread_create error: iRet = %d\n", iRet);
        return iRet;
    }
    printf("thread id in pthread = %lu\n", tid);  // 另一种方法得到线程id
    void *retval;
    iRet = pthread_join(tid, &retval);  // 等待线程结束
    if (iRet) {
        printf("pthread_join error: iRet = %d\n", iRet);
        return iRet;
    }
    printf("retval = %ld\n", (long)retval);
    return 0;
}
