#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int saldo = 0;
sem_t semaforo;



void* depositar(void* ptr)
{
    int n = *((int*)ptr);
    int i;

    for(i=0;i<1000000;i++)
    {
        sem_wait(&semaforo);
        printf("Executando thread %d...\n",n);
        saldo = saldo+1;
        sem_post(&semaforo);
    }

}

int main()
{
    int n1 = 1;
    int n2 = 2;

    sem_init(&semaforo,0,1);

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1,NULL,depositar,&n1);
    pthread_create(&thread_2,NULL,depositar,&n2);

    pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);

    printf("Saldo Final: %d.",saldo);

    return 0;
}
