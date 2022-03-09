#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/msg.h>

struct mess{
	long type;
	char buff[128];
};
int main(){
	int msgid = msgget((key_t)1234,IPC_CREAT|0600);
	assert(msgid != -1);

	struct mess dt;
	msgrcv(msgid,&dt,128,0,0);//when we accept message, can make message type "0" so that we can accept any message type.
	printf("read mess:%s\n",dt.buff);
}
