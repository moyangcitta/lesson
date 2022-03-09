#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	printf("hello\n");
	sleep(1);
	printf("hello");
	//fflush(stdout);
	sleep(2);

	_exit(0);
}
