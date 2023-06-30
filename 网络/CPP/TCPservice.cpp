#include<iostream>
#include<WinSock2.h>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")
// 1.决定做什么-加载库WSAStartup
// 2.雇佣店长-加载套接字socket
// 3.找地方-绑定IP bind
// 4.搞宣传-监听listen
// 5.客人进店-接受连接accept
// 6.点单-接收消息recvfrom
// 7.上菜-发送消息sendto
// 8.下班（店长、服务员）-关闭套接字closesocket
// 9.关门-卸载库WSACleanup

int main() {
	//1.选项目--加载库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)cout << "加载库成功" << endl;
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
	SOCKET socklisten = INVALID_SOCKET;
	socklisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//后面两个参数指的是TCP
	if (socklisten == INVALID_SOCKET) {
		printf("socket function failed with error=%d\n", WSAGetLastError());//打印错误码
		WSACleanup();
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
	err = bind(socklisten, (SOCKADDR*)&service, sizeof(service));
	if (err == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(socklisten);
		WSACleanup();
		std::system("pause");
		return 1;
	}
	else {
		printf("bind returned success\n");
	}

	//4.监听
	err = listen(socklisten, 10);//10:等待连接的最大长度
	if (err == SOCKET_ERROR) {
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(socklisten);
		WSACleanup();
		std::system("pause");
		return 1;
	}
	else {
		printf("listen returned success\n");
	}

	//5.接受连接
	sockaddr_in addClient;
	int nAddClientSize = sizeof(addClient);
	SOCKET sockClient = SOCKET_ERROR;
	int nRecvNum = 0;//按字节流接收
	char recvBuf[1024] = "";
	int recvBufLen = 1024;
	char sendBuf[1024] = "";
	while(1) {
		sockClient = accept(socklisten, (sockaddr*)&addClient, &nAddClientSize);
		if (sockClient == INVALID_SOCKET) {
			printf("accept failed with error %d\n", WSAGetLastError());
			break;
		}
		else {
			printf("accept returned success\n");
		}

		while (1) {
			//6.接收消息
			nRecvNum = recv(sockClient, recvBuf, recvBufLen, 0);
			if (nRecvNum > 0) {//接收到了
				//打印接收数据
				cout << "IP:" << inet_ntoa(addClient.sin_addr) << "say:" << recvBuf << endl;
			}
			else if (nRecvNum == 0) {
				cout << "连接已断开" << endl;
				break;
			}
			else {
				printf("recvfrom failed with error %d\n", WSAGetLastError());
				break;
			}

			//7.发送消息
			gets_s(sendBuf);
			send(sockClient, sendBuf, sizeof(sendBuf), 0);
		}
		//关闭服务员套接字
		closesocket(sockClient);
	}
	
	


	//8.下班回家--关闭套接字 卸载库
	
	closesocket(socklisten);
	WSACleanup();

	system("pause");
	return 0;
}