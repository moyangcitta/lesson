#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

int main(){
	char* s = (char*)malloc(128);
	assert(s != NULL);

	pid_t pid=fork();
	assert(pid != -1);

	if(pid == 0){
		strcpy(s,"child");
	}else{
		strcpy(s,"parent");
	}

	printf("s=%s\n",s);
	free(s);
	
	/*char* s = (char*)malloc(2*1024*1024*1024);
	assert(s != NULL);

	memset(s,0,2*1024*1024*1024);
	printf("main over\n");*/
	exit(0);
}
