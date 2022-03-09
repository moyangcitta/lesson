#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<pthread.h>

void* fun(void* arg){
	//fork();
	int i = 0;
	for(; i < 5; i++){
		printf("fun run pid=%d\n",getpid());
		sleep(1);
	}
}

int main(){
	fork();
	pthread_t id;
	pthread_create(&id,NULL,fun,NULL);

	//fork();
	int i = 0;
	for(; i < 5; i++){
		printf("main run pid=%d\n",getpid());
		sleep(1);
	}
}
