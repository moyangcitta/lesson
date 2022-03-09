#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

int main(){
	printf("main pid=%d,ppid=%d\n",getpid(),getppid());
	pid_t pid = fork();
	assert(pid != -1);

	if(pid == 0){
		printf("child pid=%d,ppid=%d\n",getpid(),getppid());
		execl("/bin/ps","ps","-f",(char*)0);
		printf("execl error");
		exit(0);
	}

	wait(NULL);

	exit(0);
}
