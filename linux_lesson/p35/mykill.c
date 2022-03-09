#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<signal.h>

//./mykill 4566 9
int main(int argc, char* argv[]){
	if(argc != 3){
		printf("argc error\n");
		return;
	}

	int pid = 0;
	int sig = 0;
	sscanf(argv[1],"%d",&pid);
	sscanf(argv[2],"%d",&sig);

	if(kill(pid,sig) == -1){
		perror("kill error");
	}

	exit(0);
}
