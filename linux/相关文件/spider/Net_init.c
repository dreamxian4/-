#include<spider.h>

int Net_init(void){
	int sockfd;
	struct sockaddr_in myaddr;
	bzero(&myaddr,sizeof(myaddr));
	
	//设置爬虫程序网络信息
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket call failed.");
		return -1;
	}

	printf("spider step[2] Net_init success.sockfd:%d\n",sockfd);
	return sockfd;
}
