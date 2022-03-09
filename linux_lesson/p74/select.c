#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/select.h>
#include<sys/time.h>
#include<stdio.h>

#define STDIN 0
int main(){
	int fd = STDIN;
	fd_set fdset;
	
	while( 1 ){
		FD_ZERO(&fdset);
		FD_SET(fd,&fdset);

		struct timeval tv = {5,0};
		int n = select(fd + 1, &fdset, NULL, NULL, &tv);
		if(n == -1){
			printf("select error\n");
			continue;
		}else if (n == 0){
			printf("time out\n");
			continue;
		}else{
			if( FD_ISSET(fd,&fdset) ){
				char buff[128] = {0};
				read(fd,buff,127);
				printf("read:%s\n",buff);
			}
		}
	}
}
