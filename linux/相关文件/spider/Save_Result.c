#include<spider.h>

int Save_Result(const char* h1,const char* desc,const char* link){
	char result[20000];
	bzero(result,sizeof(result));
	const char* start="<html>\r\n<head>\r\n<meta http-equiv=\"Content-Type\" content=\"text/hrml;charset=utf-8\">\r\n</head>\r\n<table border=\"1\" cellspacing=\"0\" cellpadding=\"0\" width=\"1900\">\r\n<caption>抓取数据集</caption>\r\n<tr><th>主标题</th><th>描述</th><th>URL地址</th></tr>";

	const char* end="</table>\r\n</html>\r\n";

	if(result_num==0){
		write(result_fd,start,strlen(start));
		return 0;//首次写入html头部
	}

	sprintf(result,"<tr id=%d><td name=\"h1\">%s</td><td name=\"description\">%s</td><td name=\"link\"><a href=\"%s\">%s</a></td></tr>\r\n",result_num,h1,desc,link,link);
	write(result_fd,result,strlen(result));

	if(result_num==RESULT_MAX){
		write(result_fd,end,strlen(end));
		close(result_fd);
	}
	return 0;
}
