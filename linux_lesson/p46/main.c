#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<pthread.h>

int wg = 0;

void* fun(void* arg){
	int i = 0;
	for(; i < 1000; i++){
		wg++;
		printf("wg=%d\n",wg);
	}
}

int main(){
	pthread_t id[5];
	int i = 0;
	for(; i < 5; i++){
		pthread_create(&id[i],NULL,fun,NULL);
	}

	for(i = 0; i < 5; i++){
		pthread_join(id[i],NULL);
	}

	exit(0);
}
