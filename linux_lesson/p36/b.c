#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<fcntl.h>

int main(){
	int fd = open("./fifo",O_RDONLY);
	assert(fd != -1);

	printf("fd=%d\n",fd);

	while(1){
		char buff[128] = {0};

		if(read(fd,buff,127) == 0){
			break;
		}
		printf("read:%s\n",buff);
	}

	close(fd);
}
