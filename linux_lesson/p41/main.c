#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/shm.h>

int main(){
	int shmid = shmget((key_t)1234,256,IPC_CREAT|0600);
	assert(shmid != -1);

	char* s = (char*)shmat(shmid,NULL,0);//return shared memory 's address
	assert(s != (char*)-1);

	strcpy(s,"hello");//copy "hello" to address "s"
	shmdt(s);
}
