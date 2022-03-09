#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<pthread.h>

void* thread_fun(void* arg){
	char buff[128] = {"a b c d e f g h w q"};
	char* ptr = NULL;
	char* s = strtok_r(buff," ",&ptr);
	while(s != NULL){
		printf("thread:s=%s\n",s);
		sleep(1);
		s = strtok_r(NULL," ",&ptr);
	}

}

int main(){
	pthread_t id;
	pthread_create(&id,NULL,thread_fun,NULL);
	char str[128] = {"1 2 3 4 5 6 7 8 9 10"};
	char* ptr = NULL;
	char* s = strtok_r(str," ",&ptr);
	while(s != NULL){
		printf("mian:%s\n",s);
		sleep(1);
		s = strtok_r(NULL," ",&ptr);
	}
}
