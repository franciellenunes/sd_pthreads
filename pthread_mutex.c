/**
* Programa : Soma Paralela com Exclusao Mútua usando Mutex
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int pthread_yield (void);

pthread_mutex_t soma_value_lock = PTHREAD_MUTEX_INITIALIZER;
int soma_global = 0;
int values_per_thread;

void *soma(void *list_ptr)
{
	int *partial_list_ptr, soma_local;
	partial_list_ptr = (int *)list_ptr;

	int id = pthread_self();
	// printf("Thread %d pronta\n",id);
	
	for (int i = 0; i < values_per_thread; i++){     
		// printf("Th %d esperando...\n",id);

		pthread_mutex_lock(&soma_value_lock);
		printf("Th: %d na secao critica\n",id);
		soma_global+= partial_list_ptr[i];
		sleep(1);
		printf("Th: %d liberou secao critica\n",id);
		pthread_mutex_unlock(&soma_value_lock);	

		pthread_yield();
	}				
	pthread_exit(NULL);
}


int main (int argc, char *argv[]) 
{

    int num_values = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
	int aux_num_values = num_values;

    pthread_t thread[num_threads];
	int values[num_values];

	int retcode;

	if (num_values < num_threads){
		printf("O número de valores deve ser maior que o número de threads!\n");
		exit(0);
	}
	 
	// aux_num_values será o valor complementar caso num_values não seja divisivel por num_threads
	if (aux_num_values % num_threads != 0) {
		while(aux_num_values % num_threads != 0){
			aux_num_values++;
		}
	}

	values_per_thread = aux_num_values / num_threads;

	// cria um array com 1
	for(int i = 0; i < num_values; i++) { values[i] = 1; }

	// adiciona ao array valores 0 para que a divisão de threads seja feita corretamente
	for(int i = num_values; i < aux_num_values; i++) { values[i] = 0; }

	// cria threads
	int cont = 0;
	for(int t = 0; t < num_threads; t++) 
	{
		// printf("Criando thread %d\n", t);

		retcode = pthread_create(&thread[t], NULL, soma, &values[cont]);
		if(retcode != 0) { printf("Erro criando thread: %d\n",t); exit(0); }

		cont += values_per_thread;
	}

	// espera threads concluirem
	for(int j = 0; j < num_threads; j++) 
	{
		retcode = pthread_join(thread[j], NULL);
		if(retcode != 0) { printf("Erro em pthread_join: %d\n",j); exit(0); }
	}

	// libera mutex
	pthread_mutex_destroy (&soma_value_lock);

	printf("Soma total: %d\n",soma_global);

	pthread_exit(NULL);
}


