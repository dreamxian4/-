#include<iostream>
#include<WinSock2.h>

using namespace std;
#pragma comment(lib,"Ws2_32.lib")

int main() {
	//加载库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)cout << "加载库成功" << endl;
	else {
		cout << "加载库失败：" << err << endl;
		system("pause");
		return 1;
	}
	
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		cout << "找不到可用版本" <<endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	//加载套接字
	SOCKET sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << "加载套接字失败：" << WSAGetLastError() << endl;
		WSACleanup();
		system("pause");
		return 1;
	}
	else cout << "加载套接字成功" << endl;

	//发送连接
	sockaddr_in addserver;
	addserver.sin_family = AF_INET;
	addserver.sin_addr.s_addr = inet_addr("192.168.1.6");
	addserver.sin_port = htons(12345);
	err = connect(sock, (SOCKADDR*)&addserver, sizeof(addserver));
	if (err != SOCKET_ERROR)cout << "连接成功" << endl;
	else {
		cout << "连接失败：" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		system("pause");
		return 1;
	}

	
	char sendBuf[1024] = "";
	int recvNum = 0;
	char recvBuf[1024] = "";
	int recvSize = 1024;
	while (1) {
		//发送信息
		gets_s(sendBuf);
		send(sock, sendBuf, sizeof(sendBuf), 0);

		//接受消息
		recvNum = recv(sock, recvBuf, recvSize, 0);
		if (recvNum > 0)cout << "服务器：" << recvBuf << endl;
		else if (recv == 0) {
			cout << "连接已断开" << endl;
			break;
		}
		else {
			cout << "接受失败：" << WSAGetLastError() << endl;
			break;
		}
	}

	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}