#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* funcao_thread(void * arg) 
{
    printf("Nova thread criada com o PID %d. \n", getpid());
    sleep(20);
    return NULL;
}

int main()
{
    pthread_t thread;
    printf("Processo pesado PID %d. \n", getpid());
    pthread_create(&thread, NULL, &funcao_thread, NULL);
    printf("Identificador do thread %d. \n", thread);
    sleep(20);
    return 0;
}
