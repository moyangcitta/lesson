#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<fcntl.h>

int main(){
	int fdr = open("/home/stu/Desktop/112.jpeg",O_RDONLY);
	int fdw = open("/home/stu/Desktop/200.jpeg",O_WRONLY|O_CREAT,0600);
	if(fdr == -1 || fdw == -1){
		exit(0);
	}

	char buff[256] = {0};
	int num = 0;

	while((num = read(fdr,buff,256)) > 0){
		write(fdw,buff,num);
	}

	close(fdr);
	close(fdw);
	/*
	int fd = open("file.txt",O_RDONLY);
	assert(fd != -1);

	char buff[128] = {0};
	int n = read(fd,buff,127);
	printf("n=%d,buff=%s\n",n,buff);

	close(fd);
	*/
	/*
	int fd = open("file.txt",O_WRONLY|O_CREAT,0600);
	assert(fd != -1);
	printf("fd=%d\n",fd);

	write(fd,"hello",5);

	close(fd);*/

	exit(0);
}
