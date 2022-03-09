#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	int i = 0;
	fork()||fork();
	printf("A\n");

	exit(0);
}
