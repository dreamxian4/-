#include<spider.h>

int Container_Get_Node(container_t* ct,url_t* node){
	if(ct->cur==0)return -1;
	*node=ct->list[ct->rear];
	ct->rear=(ct->rear+1)%ct->max;
	(ct->cur)--;
	return 0;
}
