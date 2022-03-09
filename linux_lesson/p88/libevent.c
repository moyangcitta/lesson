#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<event.h>
#include<assert.h>

void signal_cb(int fd, short event, void* arg){
	if(event & EV_SIGNAL){
		printf("sig=%d\n",fd);
	}
}

void timeout_cb(int fd, short event, void* arg){
	if(event & EV_TIMEOUT){
		printf("time out\n");
	}
}

int main(){
	struct event_base* base = event_init();
	assert(base != NULL);

	//struct event* sig_ev = evsignal_new(base,SIGINT,signal_cb,NULL);
	struct event* sig_ev = event_new(base,SIGINT,EV_SIGNAL,signal_cb,NULL);
	assert(sig_ev != NULL);

	event_add(sig_ev,NULL);

	//struct event* timeout_ev = evtimer_new(base,timeout_cb,NULL);
	struct event* timeout_ev = event_new(base,-1,EV_TIMEOUT,timeout_cb,NULL);
	struct timeval tv = {3,0};
	event_add(timeout_ev,&tv);

	event_base_dispatch(base);
	event_free(sig_ev);
	event_free(timeout_ev);
	event_base_free(base);
}
