#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<pthread.h>

pthread_mutex_t mutex;

int wg = 0;

void* fun(void* arg){
	int i = 0;
	for(; i < 1000; i++){
		pthread_mutex_lock(&mutex);
		wg++;
		printf("wg=%d\n",wg);
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	pthread_t id[5];
	pthread_mutex_init(&mutex,NULL);
	int i = 0;
	for(; i < 5; i++){
		pthread_create(&id[i],NULL,fun,NULL);
	}

	for(i = 0; i < 5; i++){
		pthread_join(id[i],NULL);
	}

	pthread_mutex_destroy(&mutex);
	exit(0);
}
