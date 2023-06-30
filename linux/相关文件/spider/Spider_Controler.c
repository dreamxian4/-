#include<spider.h>

int Spider_Controler(const char* Alpha_url){
	result_num=0;
	container_t* uct=NULL;
	container_t* pct=NULL;
	result_fd=open("result.html",O_RDWR|O_CREAT,0664);//结果文件
	Save_Result(NULL,NULL,NULL);//写入html头部
	uct=Container_Create(500);
	pct=Container_Create(RESULT_MAX);
	ssl_t* ssl=NULL;//OPENSSL
	int webfd;
	char reqhead[4096];
	url_t node;
	url_t tmpnode;

	strcpy(node.origin_url,Alpha_url);//种子URL拷贝
	if(Check_Duplication(uct,pct,node.origin_url))
		Container_Set_Node(uct,node);
	while(uct->cur>0&&result_num<RESULT_MAX){
		if(uct->cur>=100){
			analytical_shutdown=0;
			printf("analytical shutdown is close.\n");
		}else if(uct->cur<=20){
			analytical_shutdown=1;
			printf("analytical shutdown is opened.\n");
		}

		Container_Get_Node(uct,&tmpnode);
		webfd=Net_init();

		printf("%s\n",tmpnode.origin_url);
		Analytical_URL(&tmpnode);
		Connect_Webserver(&tmpnode,webfd);
		Request_Head_Create(reqhead,tmpnode);
		if(tmpnode.httptype)
			ssl=Openssl_Create(webfd);
		if((Download_Result(webfd,reqhead,tmpnode,ssl))==-1){
			continue;
		}

		Container_Set_Node(pct,tmpnode);//下载完毕，添加已处理
		Analytical_HTML(tmpnode,uct,pct);//解析HTML
	}
	printf("spider its done.result_num:%d\n",result_num);
	return 0;
}
