#include<POOL.h>

int thread_pool_destroy(thread_pool_t* ptr){
	free(ptr->queue);
	free(ptr->customer_tids);
	pthread_mutex_destroy(&ptr->lock);
	pthread_cond_destroy(&ptr->Not_full);
	pthread_cond_destroy(&ptr->Not_empty);
	free(ptr);
	return 0;
}
