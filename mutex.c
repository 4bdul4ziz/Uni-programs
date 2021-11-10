#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define NITER 1000000
pthread_mutex_t mutex;
int cnt = 0;
void *Count(void *a)
{
    int i, tmp;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < NITER; i++)
    {
        tmp = cnt;
        tmp = tmp + 1;
        cnt = tmp;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&tid1, NULL, Count, NULL))
    {
        printf("\n ERROR creating thread 1");
        exit(1);
    }
    if (pthread_create(&tid2, NULL, Count, NULL))
    {
        printf("\n ERROR creating thread 2");
        exit(1);
    }
    if (pthread_join(tid1, NULL))
    {
        printf("\n ERROR joining thread");
        exit(1);
    }
    if (pthread_join(tid2, NULL))
    {
        printf("\n ERROR joining thread");
        exit(1);
    }
    if (cnt < 2 * NITER)
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2 * NITER);
    else
        printf("\n OK! cnt is [%d]\n", cnt);
    pthread_exit(NULL);
}
