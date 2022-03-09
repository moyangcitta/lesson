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
#include<sys/epoll.h>
#include<errno.h>

#define MAXFD 10

void setnonblock(int fd){
	int oldfl = fcntl(fd,F_GETFL);
	int newfl = oldfl | O_NONBLOCK;

	if(fcntl(fd,F_SETFL,newfl) == -1){
		perror("fcntl error\n");
	}
}

void epoll_add(int epfd, int fd){
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;//r
	ev.data.fd = fd;

	setnonblock(fd);

	if(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev) == -1){
		perror("epoll ctl add err");
	}
}

void epoll_del(int epfd, int fd){
	if(epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL) == -1){
		perror("epoll ctl del err");
	}
}

int create_socket();
int main(){
	int sockfd = create_socket();
	assert(sockfd != -1);

	int epfd = epoll_create(MAXFD);
	assert(epfd != -1);

	epoll_add(epfd,sockfd);

	struct epoll_event evs[MAXFD];

	while(1){
		int n = epoll_wait(epfd,evs,MAXFD,5000);
		if(n == -1){
			perror("epol wair err\n");
			continue;
		}
		else if(n == 0){
			printf("time out\n");
			continue;
		}
		else{
			int i = 0;
			for(; i < n; i++){
				int fd = evs[i].data.fd;

				if(evs[i].events & EPOLLIN){
					if(fd == sockfd){
						struct sockaddr_in caddr;
						int len = sizeof(caddr);
						int c = accept(fd,(struct sockaddr *)&caddr,&len);
						if(c < 0){
							continue;
						}
						printf("accept c=%d\n",c);
						
						epoll_add(epfd,c);
					}
					else{
						while(1){
							char buff[128] = {0};
							int num = recv(fd,buff,1,0);
							if(num == -1){
								if(errno != EAGAIN && errno != EWOULDBLOCK){
								perror("recv err");
								}
								else{
									send(fd,"ok",2,0);
								}
								break;
							}
							else if(num == 0){
								epoll_del(epfd,fd);
								close(fd);
								printf("client close\n");
								break;
							}
							else{
								printf("rev:%s\n",buff);
							}
						}
					}
				}
				//if(evs[i].events & EPOLLOUT)
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
