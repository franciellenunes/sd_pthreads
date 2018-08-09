#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* minhathread(void * arg)
{
    printf("\t\tIniciando a thread. \n", arg);
    printf("\t\tRecebi o argumento %s do processo pesado. \n", arg);
    sleep(3);
}

int main()
{
    int retcode;
    pthread_t thread_a, thread_b;
    void * retval;
    printf("Criando a primeira thread. \n");

    /* pthread_create
    - retorna 0 no caso de sucesso
    - retorna um código de erro no caso contrário       
    */  
    retcode = pthread_create(&thread_a, NULL, &minhathread, "a");
    if(retcode != 0) 
    {
        printf("A thread não pode ser criada. Erro %d. \n", retcode);
    };
    sleep(1);
    printf("Criando a segunda thread. \n");
    retcode = pthread_create(&thread_b, NULL, &minhathread, "b");
    if(retcode != 0) 
    {
        printf("A thread não pode ser criada. Erro %d. \n", retcode);
    };
    sleep(1);
    printf("Esperando pelo término da primeira thread. \n");

 
    /* pthread_join
    - retorna 0 no caso de sucesso
    - retorna um código de erro no caso contrário       
    */    
    retcode = pthread_join(thread_a, &retval);
    printf("A primeira thread terminou. Esperando a segunda terminar. \n");
    retcode = pthread_join(thread_b, &retval);
    printf("Ambas as threads terminaram, \n");
    return 0;    
}
