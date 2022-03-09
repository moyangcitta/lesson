#include "sem.h"

static int semid = -1;

void sem_init(){
	semid = semget((key_t)1234,1,IPC_CREAT|IPC_EXCL|0600);

	if(semid == -1){
		semid = semget((key_t)1234,1,0600);//get semid
		if(semid == -1){
			perror("semget error");
		}
	}
	else{
		//initialize
		union semun a;
		a.val = 1;//semid = 1
		if(semctl(semid,0,SETVAL,a) == -1){
			perror("semctl init error");
		}
	}
}
void sem_p(){
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;//p
	buf.sem_flg = SEM_UNDO;//if programme can't work, system can help us stop programme working.

	if(semop(semid,&buf,1) == -1){
		perror("p error");
	}
}
void sem_v(){
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;//v
	buf.sem_flg = SEM_UNDO;

	if(semop(semid,&buf,1) == -1){
		perror("v error");
	}
}
void sem_destroy(){
	if(semctl(semid,0,IPC_RMID) == -1){
		perror("destroy sem error");
	}
}
