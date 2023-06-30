#include<iostream>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

int main() {
	//1.选项目--加载库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)cout << "加载库成功"<<endl;
	if (err != 0) {//err等于0，说明加载成功
		printf("WSAStartup failed with error:%d\n", err);
		std::system("pause");
		return 1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();//卸载库
		std::system("pause");
		return 1;
	}

	//2.雇人--创建套接字
	SOCKET sock = INVALID_SOCKET;//非法
	sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//三个参数分别代表：ipv4地址 使用udp协议 UDP协议
	if (sock == INVALID_SOCKET) {//创建后依然非法
		printf("socket function failed with error=%d\n", WSAGetLastError());//打印错误码
		WSACleanup();//卸载库
		std::system("pause");
		return 1;
	}
	else {
		printf("socket function succeeded\n");
	}
	
	//3.找地方摆摊--绑定IP地址
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;//绑定任意网卡
	//inet_addr 字符串转换成u_long类型
	service.sin_port = htons(12345);//端口号
	err = bind(sock, (SOCKADDR*)&service, sizeof(service));
	if (err == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		std::system("pause");
		return 1;
	}
	else {
		printf("bind returned success\n");
	}


	int nRecvNum = 0;//按字节流接收
	char recvBuf[1024] = "";
	int recvBufLen = 1024;
	sockaddr_in addrClient = { 0 };
	int addrSize = sizeof(addrClient);
	char sendBuf[1024] = "";
	while (1) {
		//4.等人来--接收消息
		nRecvNum = recvfrom(sock, recvBuf, recvBufLen, 0, (SOCKADDR*)&addrClient, &addrSize);
		if (nRecvNum > 0) {//接收到了
			//打印接收数据
			cout << "IP:" << inet_ntoa(addrClient.sin_addr) << "say:" << recvBuf << endl;
		}
		else if (nRecvNum == 0) {
			cout << "连接已断开" << endl;
			break;
		}
		else {
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			break;
		}

		//5.做东西给他--发送消息
		/*gets_s(sendBuf);
		sendto(sock, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addrClient, addrSize);*/
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