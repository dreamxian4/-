#include<spider.h>

int Analytical_URL(url_t* node){
	int flag=0;//遍历下标
	int i=0;//存储位置
	int start;//记录协议头部长度
	int filesize=0;//记录文件名长度

	const char* http[]={"http://","https://",NULL};
	bzero(node->domain,sizeof(node->domain));
	bzero(node->save_path,sizeof(node->save_path));
	bzero(node->file,sizeof(node->file));
	bzero(node->ip,sizeof(node->ip));

	//辨别协议类型，确定端口
	if((strncmp(node->origin_url,http[0],strlen(http[0])))==0){
		node->httptype=0;
		node->port=80;
		start=strlen(http[0]);
	}else{
		node->httptype=1;
		node->port=443;
		start=strlen(http[1]);
	}

	//域名
	for(flag=start;node->origin_url[flag]!='/'&&node->origin_url[flag]!='\0';flag++){
		node->domain[i]=node->origin_url[flag];
		i++;
	}
	i=0;

	//文件名长度
	for(flag=strlen(node->origin_url);node->origin_url[flag]!='/';flag--,filesize++);

	//文件名
	for(flag=strlen(node->origin_url)-filesize+1;node->origin_url[flag]!='\0';flag++){
		node->file[i]=node->origin_url[flag];
		i++;
	}
	i=0;

	//存储路径
	for(flag=start+strlen(node->domain);flag<strlen(node->origin_url)-filesize+1;flag++){
		node->save_path[i]=node->origin_url[flag];
		i++;
	}

	//DNS获取公网IP
	struct hostent* ent=NULL;
	if((ent=gethostbyname(node->domain))==NULL){
		perror("DNS gethostbyname call failed.");
		return -1;
	}

	//IP格式转换
	inet_ntop(AF_INET,ent->h_addr_list[0],node->ip,16);

	//显示结果
	printf("spider step[1],analytical_URL success.\nORIGIN_URL:%s\nDOMAIN:%s\nPATH:%s\nFILE:%s\nWEBIP:%s\nHTTPTYPE:%d\nPORT:%d\n",node->origin_url,node->domain,node->save_path,node->file,node->ip,node->httptype,node->port);
	return 0;
}
