#include<POOL.h>

int main(){
	//创建线程池
	thread_pool_t* pool=NULL;
	pool=thread_pool_create(100,10,3000);
	task_t node;
	node.busines=business;
	node.arg=NULL;

	for(int i=0;i<20;i++){
		thread_producer(pool,node);//测试任务添加
		usleep(1000);
	}
	while(1)
		sleep(1);
	return 0;
}
