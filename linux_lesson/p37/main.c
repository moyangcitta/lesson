#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<fcntl.h>

int main(){
	int fd[2];
	assert(pipe(fd) != -1);//fd[0] r, fd[1] w

	pid_t pid = fork();
	assert(pid != -1);

	if(pid == 0){
		close(fd[1]);
		char buff[128] = {0};
		read(fd[0],buff,127);
		printf("child read:%s\n",buff);
		close(fd[0]);
	}
	else{
		close(fd[0]);
		write(fd[1],"hello",5);
		close(fd[1]);
	}

	exit(0);
}
