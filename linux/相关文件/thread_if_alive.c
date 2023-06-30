#include<POOL.h>

int thread_if_alive(pthread_t tid){
	pthread_kill(tid,0);
	if(errno==ESRCH)
		return 0;//死了
	else
		return 1;//或者
}
