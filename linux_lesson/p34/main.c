#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<signal.h>

void sig_fun(int sig){
	printf("sig=%d\n",sig);
}
int main(){
	signal(SIGINT,sig_fun);
	while(1){
		printf("main run\n");
		sleep(1);
	}
}
