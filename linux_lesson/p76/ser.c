#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>

#define MAXFD 100

void fds_init(int fds[]){
	int i = 0;
	for(; i < MAXFD; i++){
		fds[i] = -1;
	}
}

void fds_add(int fds[], int fd){
	int i = 0;
	for(; i < MAXFD; i++){
		if(fds[i] == -1){
			fds[i] = fd;
			break;
		}
	}
}

void fds_del(int fds[], int fd){
	int i = 0;
	for(; i < MAXFD; i++){
		if(fds[i] == fd){
			fds[i] = -1;
			break;
		}
	}
}

int create_socket();
int main(){
	int sockfd = create_socket();
	printf("sockfd=%d\n",sockfd);
	assert(sockfd != -1);

	int fds[MAXFD];
	fds_init(fds);

	fds_add(fds,sockfd);

	fd_set fdset;

	while( 1 ){
		FD_ZERO(&fdset);
		int maxfd = -1;

		int i = 0;
		for(; i < MAXFD; i++){
			if(fds[i] != -1){
				FD_SET(fds[i],&fdset);
				if(maxfd < fds[i]){
					maxfd = fds[i];
				}
			}
		}

		struct timeval tv = {5,0};

		int n = select(maxfd + 1,&fdset,NULL,NULL,&tv);
		if(n == -1){
			printf("select error\n");
			continue;
		}else if(n == 0){
			printf("time out\n");
			continue;
		}else{
			int i = 0;
			for(; i < MAXFD; i++){
				if(fds[i] == -1){
					continue;
				}
				if(FD_ISSET(fds[i],&fdset)){
					if(fds[i] == sockfd){
						struct sockaddr_in caddr;
						int len = sizeof(caddr);
						int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
						if(c == -1){
							continue;
						}

						printf("accept c=%d\n",c);

						fds_add(fds,c);
					}else{
						char buff[128] = {0};
						int res = recv(fds[i],buff,1,0);
						if(res <= 0){
							close(fds[i]);
							fds_del(fds,fds[i]);
							printf("one client over\n");
						}else{
							printf("buff(c=%d)%s\n",fds[i],buff);
							send(fds[i],"ok",2,0);
						}
					}
				}
			}
		}
	}
}

int create_socket(){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sockfd=%d\n",sockfd);
	if(sockfd == -1){
		return -1;
	}

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	printf("res=%d\n",res);
	if(res == -1){
		return -1;
	}

	res = listen(sockfd,5);
	printf("res=%d\n",res);
	if(res == -1){
		return -1;
	}

	return sockfd;
}
