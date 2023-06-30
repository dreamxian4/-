#include<spider.h>

int Container_Set_Node(container_t* ct,url_t node){
	if(ct->cur==ct->max)return -1;
	ct->list[ct->front]=node;
	ct->front=(ct->front+1)%ct->max;
	(ct->cur)++;
	return 0;
}
