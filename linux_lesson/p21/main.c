#include<stdio.h>

int main(int argc, char* argv[], char* envp[]){
	int i = 0;
	printf("argc = %d\n",argc);
	for( ; i < argc; i++){
		printf("argv[%d] = %s\n",i,argv[i]);
	}
	
	for(i = 0; envp[i] != NULL; i++){
		printf("envp[%d] = %s\n",i,envp[i]);
	}
	return 0;
}
