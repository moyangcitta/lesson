#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include "sem.h"

int main(){
	int i = 0;
	sem_init();
	for(; i < 5; i++){
		sem_p();
		printf("A");
		fflush(stdout);
		int n = rand() % 3;
		sleep(n);
		printf("A");
		fflush(stdout);
		sem_v();

		n = rand()%3;
		sleep(n);
	}

	sleep(10);
	sem_destroy();
}
