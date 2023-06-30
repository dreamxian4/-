#include<POOL.h>

thread_pool_t* thread_pool_create(int thread_max,int thread_min,int que_max){
	//对线程程序初始化与申请内存
	thread_pool_t* ptr=NULL;
	if((ptr=(thread_pool_t*)malloc(sizeof(thread_pool_t)))==NULL){
		perror("pool_create pool_t malloc call failed.");
		exit(0);
	}
	ptr->thread_shutdown=TRUE;//1开启 0关闭
	ptr->thread_max=thread_max;
	ptr->thread_min=thread_min;
	ptr->thread_alive=0;
	ptr->thread_busy=0;
	ptr->thread_exitcode=0;

	if((ptr->queue=(task_t*)malloc(sizeof(task_t)))==NULL){
		perror("pool_create queue malloc call failed.");
		exit(0);
	}
	ptr->FRONT=0;
	ptr->REAR=0;
	ptr->CUR=0;
	ptr->MAX=que_max;

	if(pthread_mutex_init(&ptr->lock,NULL)!=0||pthread_cond_init(&ptr->Not_full,NULL)!=0||pthread_cond_init(&ptr->Not_empty,NULL)!=0){
		perror("pool_create lock init call failed.");
		exit(0);
	}

	if((ptr->customer_tids=(pthread_t*)malloc(sizeof(pthread_t)*thread_max))==NULL){
		perror("pool_create tid malloc call failed.");
		exit(0);
	}

	//初始化tids数组
	bzero(ptr->customer_tids,sizeof(pthread_t)*thread_max);
		
	//预创建消费者线程待用
	int err;
	for(int i=0;i<thread_min;i++){
		if((err=pthread_create(&ptr->customer_tids[i],NULL,thread_customer,(void*)ptr))>0){
			printf("pool_create customer_thread call failed.errno:%s\n",strerror(err));
			exit(0);
		}
		++(ptr->thread_alive);//存活线程+1
	}
	
	//创建管理线程
	if((err=pthread_create(&ptr->manager_tid,NULL,thread_manager,(void*)ptr))>0){
		printf("pool_create manager_thread call failed.errno:%s\n",strerror(err));
		exit(0);
	}

	return ptr;
}
