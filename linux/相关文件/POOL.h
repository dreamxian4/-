#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<pthread.h>
#include<errno.h>

#define _SERVER_TP 192.168.244.131
#define _SERVER_PORT 8080
#define TRUE 1
#define FALSE 0
#define _BUFSIZE 1500
#define _EPOLLMAX 100000
#define _BACKLOG 128
#define _IPSIZE 16
#define _DFLCODE 10

typedef struct{
	void* (*busines)(void*);
	void* arg;
}task_t;//任务

typedef struct{
	int thread_shutdown;
	int thread_max;
	int thread_min;
	int thread_alive;
	int thread_busy;
	int thread_exitcode;//缩减

	task_t* queue;
	int FRONT;
	int REAR;
	int MAX;
	int CUR;
	pthread_mutex_t lock;
	pthread_cond_t Not_full;
	pthread_cond_t Not_empty;

       	pthread_t manager_tid;
	pthread_t* customer_tids;
}thread_pool_t;//线程池

thread_pool_t* thread_pool_create(int,int,int);
int thread_producer(thread_pool_t*,task_t);
void* thread_manager(void*);
void* thread_customer(void*);
int thread_pool_destroy(thread_pool_t*);
void* business(void*);//测试任务接口
int thread_if_alive(pthread_t);
