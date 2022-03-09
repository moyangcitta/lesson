#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

int main()
{
	char* s = NULL;
	int n = 0;

	pid_t id = fork();
	assert(id != -1);

	if(id == 0)
	{
		s = "child";
		n = 3;
	}
	else
	{
		s = "parent";
		n = 7;
		int val = 0;
		wait(&val);
		if(WIFEXITED(val)){
		
			printf("val=%d\n",WEXITSTATUS(val));
		}
	}

	int i = 0;
	for(; i < n; i++){
		printf("s=%s,pid=%d,ppid=%d,n=%d,&n=%x\n",s,getpid(),getppid(),n,&n);
		sleep(1);
	}
	exit(3);
}
