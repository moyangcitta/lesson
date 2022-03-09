#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<fcntl.h>

int main(){
	int fd = open("./fifo",O_WRONLY);
	printf("fd=%d\n",fd);
	assert(fd != -1);

	while(1){
		printf("input:\n");
		char buff[128] = {0};
		fgets(buff,128,stdin);
		if(strncmp(buff,"end",3) == 0){
			break;
		}
		write(fd,buff,strlen(buff));
	}

	close(fd);
}
