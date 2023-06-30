#include<POOL.h>

int thread_producer(thread_pool_t* ptr,task_t node){
	if(ptr->thread_shutdown){
		pthread_mutex_lock(&ptr->lock);
		while(ptr->CUR==ptr->MAX){
			pthread_cond_wait(&ptr->Not_full,&ptr->lock);
		}
		if(!(ptr->thread_shutdown)){
			pthread_mutex_unlock(&ptr->lock);
			pthread_exit(NULL);//生产者线程退出(主线程)
		}
		//添加任务过程
		ptr->queue[ptr->FRONT].busines=node.busines;
		ptr->queue[ptr->FRONT].arg=node.arg;
		ptr->FRONT=(ptr->FRONT+1)%ptr->MAX;
		++(ptr->CUR);
		pthread_mutex_unlock(&ptr->lock);
		pthread_cond_signal(&ptr->Not_empty);
	}else{
		pthread_exit(NULL);
	}
	return 0;
}
