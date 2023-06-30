#include<spider.h>

int Get_statcode(char* reshead){
	int code;
	char str_code[10];//字符串响应码
	bzero(str_code,sizeof(str_code));
	//HTTP/1.1 200 OK
	
	regex_t reg;
	regmatch_t match[2];

	regcomp(&reg,"HTTP/1.1 \\([^\r\n]\\+\\?\\)",0);
	if((regexec(&reg,reshead,2,match,0))==0){
		snprintf(str_code,match[1].rm_eo-match[1].rm_so+1,"%s",reshead+match[1].rm_so);
		sscanf(str_code,"%d",&code);
		regfree(&reg);
		return code;
	}
	regfree(&reg);
	return -1;
}
