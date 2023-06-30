#include<spider.h>

int Request_Head_Create(char* reqhead,url_t node){
	bzero(reqhead,4096);//初始化请求头数组
	sprintf(reqhead,"GET %s HTTP/1.1\r\n"\
			"Accept:text/html,application/shtml+xml;q=0.9,image/webp;q=0.8\r\n"\
			"User-Agent:Mozilla/5.0 (X11; Linux x86_64)\r\n"\
			"Host:%s\r\n"\
			"Connection:close\r\n\r\n",node.origin_url,node.domain);
	printf("spider step[4] Request_Head_Create success.\n%s",reqhead);
	return 0;
}
