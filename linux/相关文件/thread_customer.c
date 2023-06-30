#include<POOL.h>

void* thread_customer(void* arg){
	thread_pool_t* ptr=NULL;
	ptr=(thread_pool_t*)arg;
	task_t job;
	while(ptr->thread_shutdown){
		pthread_mutex_lock(&ptr->lock);
		if(ptr->CUR==0){
			pthread_cond_wait(&ptr->Not_empty,&ptr->lock);
			if(ptr->thread_exitcode>0){
				--(ptr->thread_exitcode);
				--(ptr->thread_alive);
				pthread_mutex_unlock(&ptr->lock);
				pthread_exit(NULL);
			}
		}
		if(!(ptr->thread_shutdown)){
			--(ptr->thread_alive);
			pthread_mutex_unlock(&ptr->lock);
			pthread_exit(NULL);
		}
		job.busines=ptr->queue[ptr->REAR].busines;
		job.arg=ptr->queue[ptr->REAR].arg;
		ptr->REAR=(ptr->REAR+1)%ptr->MAX;
		--(ptr->CUR);

		++(ptr->thread_busy);
		pthread_mutex_unlock(&ptr->lock);
		pthread_cond_signal(&ptr->Not_full);

		(job.busines)(job.arg);

		pthread_mutex_lock(&ptr->lock);
		--(ptr->thread_busy);
		pthread_mutex_unlock(&ptr->lock);
	}
	pthread_exit(NULL);
}
