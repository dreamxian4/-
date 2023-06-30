#include<spider.h>

int Analytical_HTML(url_t node,container_t* uct,container_t* pct){
	int html_fd;
	int html_size;
	char* html_ptr=NULL;//映射地址
	char* copy_html_ptr=NULL;//备份映射地址
	char h1[1024];
	char desc[8192];
	char link[8192];
	url_t tmpnode;
	regex_t h1_reg,desc_reg,link_reg;
	regmatch_t h1_mh[2];
	regmatch_t desc_mh[2];
	regmatch_t link_mh[2];
	bzero(h1,sizeof(h1));
	bzero(desc,sizeof(desc));
	bzero(link,sizeof(link));

	html_fd=open(node.file,0,O_RDONLY);//打开源码文件
	html_size=lseek(html_fd,0,SEEK_END);//获取源码文件大小

	if((html_ptr=mmap(NULL,html_size,PROT_READ,MAP_PRIVATE,html_fd,0))==MAP_FAILED){
		perror("Analytical html call failed.mmap error.");
		exit(0);
	}
	copy_html_ptr=html_ptr;//备份首地址
	close(html_fd);

	//根据数据规则编写正则语句
	regcomp(&h1_reg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);
	regcomp(&desc_reg,"<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">",0);
	regcomp(&link_reg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>",0);

	//使用正则语句在数据源中进行模式匹配
	if((regexec(&h1_reg,html_ptr,2,h1_mh,0))==0){
		snprintf(h1,h1_mh[1].rm_eo-h1_mh[1].rm_so+1,"%s",html_ptr+h1_mh[1].rm_so);
	}
	if((regexec(&desc_reg,html_ptr,2,desc_mh,0))==0){
		snprintf(desc,desc_mh[1].rm_eo-desc_mh[1].rm_so+1,"%s",html_ptr+desc_mh[1].rm_so);
	}
	(result_num)++;//抓取数量+1
	//将提取的兴趣数据持久化到数据库或磁盘中
	Save_Result(h1,desc,node.origin_url);//存储

	if(analytical_shutdown){
		while((regexec(&link_reg,html_ptr,2,link_mh,0))==0){
			snprintf(link,link_mh[1].rm_eo-link_mh[1].rm_so+24,"https://baike.baidu.com%s",html_ptr+link_mh[1].rm_so);//拼接前缀
			//新连接去重校验，添加到未处理队列，等待处理
			if(Check_Duplication(uct,pct,link)){
				strcpy(tmpnode.origin_url,link);
				Container_Set_Node(uct,tmpnode);//添加未处理
			}
			bzero(link,sizeof(link));
			html_ptr+=link_mh[1].rm_eo;
			if(uct->cur+1==uct->max){
				printf("container uct its full.\n");
				break;
			}
		}
	}
	//删除源码
	unlink(node.file);
	//释放正则
	regfree(&h1_reg);
	regfree(&desc_reg);
	regfree(&link_reg);
	munmap(copy_html_ptr,html_size);
	return 0;
}
