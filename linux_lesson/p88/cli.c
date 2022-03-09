#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
	//socket() connect() send() recv() close()
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);

	while(1){
		printf("intput:\n");
		char buff[128] = {0};
		fgets(buff,127,stdin);
		if(strncmp(buff,"end",3) == 0){
			break;
		}
		send(sockfd,buff,strlen(buff),0);//write()

		memset(buff,0,128);
		recv(sockfd,buff,127,0);//read()
		printf("read:%s\n",buff);
	}
	close(sockfd);
}
