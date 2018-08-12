#include <pthread.h>
#include <stdio.h>

/**
* Neste exemplo duas novas threads são criadas. 
* A primeira irá contar de 0 a 99 e a segunda irá contar de 100 a 199. 
* A thread main cria uma nova thread ProcessoLeve1 com a chama da primitiva pthread_create(). 
* A seguir a thread main se bloqueia com a primitiva pthread_join(ProcessoLeve1, NULL). Ess primitiva fica à espera de que ProcessoLeve1 termine. 
* Após o término, a thread main cria a thread ProcessoLeve2 
* A thread main de bloqueia novamente com a operação pthread_join(ProcessoLeve2, NULL) até que se acabe.
* 
* Neste exemplo, o uso da primitiva pthread_join() é indispensável, pois impede que o processo pesado - thread main - continue a execução e termine. 
* Se isso acontecesse, os processos leves seriam eliminados antes da hora.
*
* Uma maneira de contornar isso, é desconectar as threads ProcessoLeve1 e ProcessoLeve2 incluindo a função detach
*/

void * ProcessoLeve1()
{	
	// pthread_detach(pthread_self());
	for(int i = 1; i < 100; i++){
		printf("\tThread 1 - %d \n", i);
	}
	pthread_exit(NULL);
}

void * ProcessoLeve2()
{
	// pthread_detach(pthread_self());
	for(int j = 100; j < 200; j++){
		printf("\tThread 2 - %d \n", j);
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	int retcode;
	pthread_t thread1, thread2;
	
	retcode = pthread_create(&thread1, NULL, &ProcessoLeve1, NULL);
	if(retcode){
		printf("Erro %d na criação da thread1 \n", retcode);
	}
	pthread_join(thread1, NULL);
	
	retcode = pthread_create(&thread2, NULL, &ProcessoLeve2, NULL);	
	if(retcode){
		printf("Erro %d na criação da thread2 \n", retcode);
	}
	pthread_join(thread2, NULL);
	
	printf("FIM\n");
	pthread_exit(NULL);
}