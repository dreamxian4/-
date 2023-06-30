#include<POOL.h>

void* business(void* arg){
	printf("0x%x kaishi.\n",(unsigned int)pthread_self());
	sleep(10);
	return NULL;
}
