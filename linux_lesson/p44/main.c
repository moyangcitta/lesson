#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<pthread.h>

void* fun(void* arg){//son thread
	int i = 0;
	for(; i < 10; i++){
		printf("fun run\n");
		sleep(1);
	}
	pthread_exit("fun over");
}
int main(){//main fun
	pthread_t id;
	pthread_create(&id,NULL,fun,NULL);

	int i = 0;
	for(; i < 5; i++){
		printf("main run\n");
		sleep(1);
	}

	char* s = NULL;
	pthread_join(id,(void**)&s);//clog,and waiting son thread end 
	printf("join:s=%s\n",s);
	exit(0);
}
