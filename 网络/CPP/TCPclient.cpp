#include<iostream>
#include<WinSock2.h>

using namespace std;
#pragma comment(lib,"Ws2_32.lib")

int main() {
	//���ؿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)cout << "���ؿ�ɹ�" << endl;
	else {
		cout << "���ؿ�ʧ�ܣ�" << err << endl;
		system("pause");
		return 1;
	}
	
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		cout << "�Ҳ������ð汾" <<endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	//�����׽���
	SOCKET sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << "�����׽���ʧ�ܣ�" << WSAGetLastError() << endl;
		WSACleanup();
		system("pause");
		return 1;
	}
	else cout << "�����׽��ֳɹ�" << endl;

	//��������
	sockaddr_in addserver;
	addserver.sin_family = AF_INET;
	addserver.sin_addr.s_addr = inet_addr("192.168.1.6");
	addserver.sin_port = htons(12345);
	err = connect(sock, (SOCKADDR*)&addserver, sizeof(addserver));
	if (err != SOCKET_ERROR)cout << "���ӳɹ�" << endl;
	else {
		cout << "����ʧ�ܣ�" << WSAGetLastError() << endl;
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
		//������Ϣ
		gets_s(sendBuf);
		send(sock, sendBuf, sizeof(sendBuf), 0);

		//������Ϣ
		recvNum = recv(sock, recvBuf, recvSize, 0);
		if (recvNum > 0)cout << "��������" << recvBuf << endl;
		else if (recv == 0) {
			cout << "�����ѶϿ�" << endl;
			break;
		}
		else {
			cout << "����ʧ�ܣ�" << WSAGetLastError() << endl;
			break;
		}
	}

	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}