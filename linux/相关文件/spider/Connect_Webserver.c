#include<spider.h>

int Connect_Webserver(url_t* node,int webfd){
	struct sockaddr_in webaddr;
	bzero(&webaddr,sizeof(webaddr));
	webaddr.sin_family=AF_INET;
	webaddr.sin_port=htons(node->port);
	inet_pton(AF_INET,node->ip,&webaddr.sin_addr.s_addr);

	if((connect(webfd,(struct sockaddr*)&webaddr,sizeof(webaddr)))==-1){
		perror("connect call failed.");
		return -1;
	}

	printf("spider step[3] Connect_Webserver success.\n");
	return 0;
}
