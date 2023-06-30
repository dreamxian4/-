#include<spider.h>

int Download_Result(int webfd,char* reqhead,url_t node,ssl_t* ssl){
	int code;//存储响应码
	char buffer[8192];//读取缓冲区
	char response_head[4096];//响应头缓冲区
	int recvlen;//读取大小
	char* pos=NULL;//存储空行地址
	int fd;//存储资源文件的描述符
	bzero(buffer,8192);
	bzero(response_head,4096);

	//发送请求头
	SSL_write(ssl->sslsocket,reqhead,strlen(reqhead));
	printf("spider step[5] send request.\n");
	//首次读取响应
	recvlen=SSL_read(ssl->sslsocket,buffer,sizeof(buffer));
	//查找空行地址
	if((pos=strstr(buffer,"\r\n\r\n"))==NULL){
		printf("strstr call failed,not find.\n");
		close(webfd);
		return -1;
	}
	//存储响应头
	snprintf(response_head,pos-buffer+4,"%s",buffer);
	printf("spider step[6] get response head:\n%s",response_head);

	if((code=Get_statcode(buffer))==200){
		printf("spider get statcode:%d\n",code);
		fd=open(node.file,O_RDWR|O_CREAT,0664);
		//将首次读取剩余的部分响应体写入文件
		write(fd,pos+4,recvlen-(pos-buffer+4));
		while((recvlen=SSL_read(ssl->sslsocket,buffer,sizeof(buffer)))>0){
			write(fd,buffer,recvlen);
			bzero(buffer,sizeof(buffer));
		}
		close(fd);
	}else{
		printf("spider download result failed response code:%d\n",code);
		free(ssl);
		ssl=NULL;
		close(webfd);
		return -1;
	}
	free(ssl);
	ssl=NULL;
	close(webfd);
	return 0;
}
