#include<spider.h>

int Check_Duplication(container_t* uct,container_t* pct,const char* url){
	int flag;
	flag=uct->rear;//尾索引
	while(flag%uct->max!=uct->front){
		if((strncmp(uct->list[flag].origin_url,url,strlen(url)))==0)
			return 0;
		flag++;
	}

	flag=pct->rear;
	while(flag%pct->max!=pct->front){
		if((strncmp(pct->list[flag].origin_url,url,strlen(url)))==0)
			return 0;
		flag++;
	}
	return 1;//无重复，新链接
}
