#include<spider.h>

ssl_t* Openssl_Create(int webfd){
	ssl_t* ssl=NULL;
	ssl=(ssl_t*)malloc(sizeof(ssl_t));//申请内存

	SSL_load_error_strings();//加载ssl错误处理函数
	SSL_library_init();//初始化openssl库函数
	OpenSSL_add_ssl_algorithms();//初始化加密方式，散列函数
	ssl->sslctx=SSL_CTX_new(SSLv23_method());//生成ssl版本信息存储在ctx中
	ssl->sslsocket=SSL_new(ssl->sslctx);//使用ssl版本信息创建对应的ssl安全套接字
	SSL_set_fd(ssl->sslsocket,webfd);//使用wevfd设置安全套接字，使其与web服务器关联

	//进行http认证，单向认证
	SSL_connect(ssl->sslsocket);

	//认证完毕后，后续使用sslsocket进行数据传输，必须加密传输
	//SSL_read() 读取并解密数据 SSL_write() 加密并发送数据
	return ssl;
}
