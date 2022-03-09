#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>

int create_socket();

int main(){
	int sockfd = create_socket();
	assert( sockfd != -1 );

	while( 1 ){
		struct sockaddr_in caddr;
		int len = sizeof(caddr);

		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if( c < 0 ){
			continue;
		}

		char buff[1024] = {0};
		int n = recv(c,buff,1023,0);
		printf("n=%d,read:\n",n);
		printf("%s\n",buff);

		char* s = strtok(buff," ");
		if(s == NULL){
			send(c,"400",3,0);
			close(c);
			continue;
		}

		printf("REQUEST METHOD:%s\n",s);
		s = strtok(NULL," ");
		if(s == NULL){
			send(c,"404",3,0);
			close(c);
			continue;
		}

		printf("REQUEST RESQUSE:%s\n",s);

		if(strcmp(s,"/") == 0){
			s = "index.html";
		}

		char path[128] = {"/home/stu/lesson/p69"};
		strcat(path,s);

		int fd = open(path,O_RDONLY);
		if( fd == -1 ){
			send(c,"404",3,0);
			close(c);
			continue;
		}

		int size = lseek(fd,0,SEEK_END);
		lseek(fd,0,SEEK_SET);

		//send(c,"i love you, zhou yue!",22,0);
		char sendbuff[512] = {0};
		strcpy(sendbuff,"HTTP/1.1 200 OK\r\n");
		strcat(sendbuff,"Server: myhttp\r\n");
		//strcat(sendbuff,"Content-Length: 20\r\n");
		sprintf(sendbuff + strlen(sendbuff),"Content-Length: %d\r\n",size);
		strcat(sendbuff,"\r\n");

		//strcat(sendbuff,"i love you, zhou yue");
		printf("send:\n%s\n",sendbuff);
		send(c,sendbuff,strlen(sendbuff),0);

		char data[512] = {0};
		int num = 0;
		while( ( num = read(fd,data,512) ) > 0 ){
			send(c,data,num,0);
		}
		
		close(fd);
		close(c);
	}
}

int create_socket(){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		return -1;
	}

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(80);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if( res == -1){
		return -1;
	}

	res = listen(sockfd,5);
	if( res == -1 ){
		return -1;
	}

	return sockfd;
}
