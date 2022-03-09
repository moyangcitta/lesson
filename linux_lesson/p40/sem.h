#include<sys/sem.h>
#include<unistd.h>

union semun{
	int val;
};

void sem_init();
void sem_p();
void sem_v();
void sem_destroy();
