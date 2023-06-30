#include<iostream>
#include<WinSock2.h>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")
// 1.������ʲô-���ؿ�WSAStartup
// 2.��Ӷ�곤-�����׽���socket
// 3.�ҵط�-��IP bind
// 4.������-����listen
// 5.���˽���-��������accept
// 6.�㵥-������Ϣrecvfrom
// 7.�ϲ�-������Ϣsendto
// 8.�°ࣨ�곤������Ա��-�ر��׽���closesocket
// 9.����-ж�ؿ�WSACleanup

int main() {
	//1.ѡ��Ŀ--���ؿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)cout << "���ؿ�ɹ�" << endl;
	if (err != 0) {//err����0��˵�����سɹ�
		printf("WSAStartup failed with error:%d\n", err);
		std::system("pause");
		return 1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();//ж�ؿ�
		std::system("pause");
		return 1;
	}

	//2.����--�����׽���
	SOCKET socklisten = INVALID_SOCKET;
	socklisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//������������ָ����TCP
	if (socklisten == INVALID_SOCKET) {
		printf("socket function failed with error=%d\n", WSAGetLastError());//��ӡ������
		WSACleanup();
		std::system("pause");
		return 1;
	}
	else {
		printf("socket function succeeded\n");
	}

	//3.�ҵط���̯--��IP��ַ
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;//����������
	//inet_addr �ַ���ת����u_long����
	service.sin_port = htons(12345);//�˿ں�
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

	//4.����
	err = listen(socklisten, 10);//10:�ȴ����ӵ���󳤶�
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

	//5.��������
	sockaddr_in addClient;
	int nAddClientSize = sizeof(addClient);
	SOCKET sockClient = SOCKET_ERROR;
	int nRecvNum = 0;//���ֽ�������
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
			//6.������Ϣ
			nRecvNum = recv(sockClient, recvBuf, recvBufLen, 0);
			if (nRecvNum > 0) {//���յ���
				//��ӡ��������
				cout << "IP:" << inet_ntoa(addClient.sin_addr) << "say:" << recvBuf << endl;
			}
			else if (nRecvNum == 0) {
				cout << "�����ѶϿ�" << endl;
				break;
			}
			else {
				printf("recvfrom failed with error %d\n", WSAGetLastError());
				break;
			}

			//7.������Ϣ
			gets_s(sendBuf);
			send(sockClient, sendBuf, sizeof(sendBuf), 0);
		}
		//�رշ���Ա�׽���
		closesocket(sockClient);
	}
	
	


	//8.�°�ؼ�--�ر��׽��� ж�ؿ�
	
	closesocket(socklisten);
	WSACleanup();

	system("pause");
	return 0;
}