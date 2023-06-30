#include<iostream>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

int main() {
	//1.选项目--加载库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);//2.2版本号
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {//err等于0，说明加载成功
		printf("WSAStartup failed with error:%d\n", err);
		std::system("pause");
		return 1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {//判断版本号是否为2.2
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();//卸载库
		std::system("pause");
		return 1;
	}

	//2.雇人--创建套接字
	SOCKET sock = INVALID_SOCKET;//非法
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//三个参数分别代表：ipv4地址 使用udp协议 UDP协议
	if (sock == INVALID_SOCKET) {//创建后依然非法
		printf("socket function failed with error=%d\n", WSAGetLastError());//打印错误码（工具->错误查找->输入错误码）
		WSACleanup();//卸载库
		std::system("pause");
		return 1;
	}
	else {
		printf("socket function succeeded\n");
	}

	//定义服务端的IP地址，给其发送消息
	sockaddr_in addrservice;
	addrservice.sin_family = AF_INET;
	addrservice.sin_addr.s_addr = inet_addr("192.168.244.1");//服务器端的IP地址
	addrservice.sin_port = htons(12345);//端口号
	int addrSize = sizeof(addrservice);

	char sendBuf[1024] = "";//发送的数据
	int nRecvNum = 0;//按字节流接收
	char recvBuf[1024] = "";
	int recvBufLen = 1024;
	while (1) {
		//3.到店点餐--发送消息
		gets_s(sendBuf);
		sendto(sock, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addrservice, addrSize);

		//4.取餐--接收消息
		nRecvNum = recvfrom(sock, recvBuf, recvBufLen, 0, 0, 0);//自己主动发送的，不需要接收服务器端的IP地址
		if (nRecvNum > 0) {//接收到了
			//打印接收数据
			cout << "服务器: " << recvBuf << endl;
		}
		else if (nRecvNum == 0) {
			cout << "连接已断开" << endl;
			closesocket(sock);
			WSACleanup();
			std::system("pause");
			return 1;
		}
		else {
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			std::system("pause");
			return 1;
		}
	}

	//6.下班回家--关闭套接字 卸载库
	err = closesocket(sock);
	if (err == SOCKET_ERROR) {
		printf("closesocket failed with error%u\n", WSAGetLastError());
	}
	WSACleanup();
	std::system("pause");
	return 0;
}