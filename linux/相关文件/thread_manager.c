#include<POOL.h>

void* thread_manager(void* arg){
	pthread_detach(pthread_self());
	thread_pool_t* ptr=(thread_pool_t*)arg;
	int alive,cur,busy;
	int flag;//遍历下标
	int add;//创建数量
	int err;
	while(ptr->thread_shutdown){
		pthread_mutex_lock(&ptr->lock);
		busy=ptr->thread_busy;
		alive=ptr->thread_alive;
		cur=ptr->CUR;
		pthread_mutex_unlock(&ptr->lock);
		if((cur>=alive-busy||(double)busy/alive*100>=(double)70)&&alive+_DFLCODE<=ptr->thread_max){
			for(flag=0,add=0;flag<ptr->thread_max&&add<_DFLCODE;flag++){
				if((err=pthread_create(&ptr->customer_tids[flag],NULL,thread_customer,(void*)ptr))>0){
					printf("manager thread_create call failed.errno:%s\n",strerror(err));
					exit(0);
				}
				add++;
				pthread_mutex_lock(&ptr->lock);
				++(ptr->thread_alive);
				pthread_mutex_unlock(&ptr->lock);
			}
		}

		if(busy*2<=alive-busy&&alive-_DFLCODE>=ptr->thread_min){
			pthread_mutex_lock(&ptr->lock);
			ptr->thread_exitcode=_DFLCODE;
			pthread_mutex_unlock(&ptr->lock);

			for(int i=0;i<_DFLCODE;i++){
				pthread_cond_signal(&ptr->Not_empty);
			}		
		}

		sleep(2);
	}
	pthread_exit(NULL);
}
