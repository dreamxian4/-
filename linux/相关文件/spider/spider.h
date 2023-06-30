#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<regex.h>
#include<sys/mman.h>
#include<sys/socket.h>
#include<netdb.h>//DNS
#include<openssl/ssl.h>
#include<openssl/err.h>

//https://baike.baidu.com/item/%E5%8E%9F%E7%A5%9E/23583622?fr=aladdin

#define RESULT_MAX 1000
int result_num;
int result_fd;//兴趣数据保存位置
int analytical_shutdown;//1开启html解析新连接，0关闭html解析新连接（控制新连接解析速度，当未处理队列中待处理少于某个值解析新连接，否则先处理下载

//url存储类型
typedef struct{
	char origin_url[8192];
	char domain[4096];
	char save_path[1024];
	char file[1024];
	char ip[16];
	int httptype;//http:0 https:1
	int port;//http:80 https:443
}url_t;

//环形对列
typedef struct{
	url_t* list;
	int front;
	int rear;
	int cur;
	int max;
}container_t;

//ssl类型
typedef struct{
	SSL* sslsocket;//安全套接字
	SSL_CTX* sslctx;//SSL版本信息及上下文信息（完成认证通信后续加密通信数据）
}ssl_t;

int Analytical_URL(url_t* node);//传入之包含origin_url的node,解析完毕传出完整的node
int Analytical_HTML(url_t node,container_t* uct,container_t* pct);//html网页源码解析，提取兴趣数据，解析更多词条链接
int Net_init(void);//爬虫创建套接字
int Connect_Webserver(url_t* node,int webfd);//TCP连接web服务器
ssl_t* Openssl_Create(int webfd);//ssl安全套接字创建及安全认证过程
int Request_Head_Create(char* reqhead,url_t node);//创建请求头
int Download_Result(int webfd,char* reqhead,url_t node,ssl_t* ssl);//与web服务器进行交互，下载持久化数据
int Get_statcode(char* reshead);//从响应头中匹配读取响应码，转换为整型后返回

//容器相关
container_t* Container_Create(int max);
int Container_Set_Node(container_t* ct,url_t node);
int Container_Get_Node(container_t* ct,url_t* node);
//遍历去重
int Check_Duplication(container_t* uct,container_t* pct,const char* url);
int Save_Result(const char* h1,const char* desc,const char* link);

//爬虫控制器，执行流程
int Spider_Controler(const char* Alpha_URL);
