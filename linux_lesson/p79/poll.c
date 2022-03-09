#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<poll.h>

#define MAXFD 10

void fds_init(struct pollfd fds[]){
	int i = 0;
	for(; i < MAXFD; i++){
		fds[i].fd = -1;
		fds[i].events = 0;
		fds[i].revents = 0;
	}
}

void fds_add(struct pollfd fds[], int fd){
	int i = 0;
	for(; i < MAXFD; i++){
		if(fds[i].fd == -1){
			fds[i].fd = fd;
			fds[i].events = POLLIN;//r
			fds[i].revents = 0;
			break;
		}
	}
}

void fds_del(struct pollfd fds[], int fd){
	int i = 0;
	for(; i < MAXFD; i++){
		if(fds[i].fd == fd){
			fds[i].fd = -1;
			fds[i].events = 0;
			fds[i].revents = 0;
		}
	}
}

int create_socket();
int main(){
	int sockfd = create_socket();
	//printf("sockfd=%d\n",sockfd);
	assert(sockfd != -1);

	struct pollfd fds[MAXFD];
	fds_init(fds);

	fds_add(fds,sockfd);

	while(1){
		int n = poll(fds,MAXFD,5000);//stop
		if(n == -1){
			continue;
		}
		else if(n == 0){
			printf("time out\n");
			continue;
		}
		else{
			int i = 0;
			for(; i < MAXFD; i++){
				if(fds[i].fd == -1){
					continue;
				}
				if(fds[i].revents & POLLIN){
					if(fds[i].fd == sockfd){
						struct sockaddr_in caddr;
						int len = sizeof(caddr);
						int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
						if(c < 0){
							continue;
						}
						printf("accept c=%d\n",c);
						fds_add(fds,c);
					}
					else{
						char buff[128] = {0};
						int num = recv(fds[i].fd,buff,127,0);
						if(num <= 0){
							close(fds[i].fd);
							fds_del(fds,fds[i].fd);
							printf("client close\n");
							continue;
						}

						printf("buff(%d)=%s\n",fds[i].fd,buff);
						send(fds[i].fd,"ok",2,0);
					}
				}
				//if(fds[i].revents & POLLOUT)
			}
		}
	}
}

int create_socket(){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	//printf("sockfd=%d\n",sockfd);
	if(sockfd == -1){
		return -1;
	}

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	//printf("res=%d\n",res);
	if(res == -1){
		return -1;
	}

	res = listen(sockfd,5);
	//printf("res=%d\n",res);
	if(res == -1){
		return -1;
	}
	//printf("sockfd=%d\n",sockfd);
	return sockfd;
}
