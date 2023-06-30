#include<spider.h>

container_t* Container_Create(int max){
	container_t* ct=NULL;
	if((ct=(container_t*)malloc(sizeof(container_t)))==NULL){
		perror("container create call failed.malloc container error.\n");
		exit(0);
	}
	if((ct->list=(url_t*)malloc(sizeof(url_t)*max))==NULL){
		perror("container create call failed.malloc list error.\n");
		exit(0);
	}
	ct->front=0;
	ct->rear=0;
	ct->cur=0;
	ct->max=max;
	printf("%d %d %d %d\n",ct->front,ct->rear,ct->cur,ct->max);
	return ct;
}
