#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

int main(){
	int i = 0;
	for(; i < 5; i++){
		printf("A");
		fflush(stdout);
		int n = rand() % 3;
		sleep(n);
		printf("A");
		fflush(stdout);
		n = rand()%3;
		sleep(n);
	}
}
