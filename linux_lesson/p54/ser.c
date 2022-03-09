#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr,caddr;
	memset(&saddr,0,sizeof(saddr));//clear saddr
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);

	listen(sockfd,5);

	while(1){
		int len = sizeof(saddr);
		printf("accept wait...\n");
		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c < 0){
			continue;
		}

		printf("accept c = %d\n",c);

		while(1){
			
			char buff[128] = {0};
			int n = recv(c,buff,1,0);//read
			if(n <= 0){
				break;
			}

			printf("buff=%s\n",buff);
			send(c,"ok",2,0);//write
		}
		close(c);
	}
}
