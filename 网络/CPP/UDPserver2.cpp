#include<iostream>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

int main() {
	//1.ѡ��Ŀ--���ؿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)cout << "���ؿ�ɹ�"<<endl;
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
	SOCKET sock = INVALID_SOCKET;//�Ƿ�
	sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//���������ֱ����ipv4��ַ ʹ��udpЭ�� UDPЭ��
	if (sock == INVALID_SOCKET) {//��������Ȼ�Ƿ�
		printf("socket function failed with error=%d\n", WSAGetLastError());//��ӡ������
		WSACleanup();//ж�ؿ�
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


	int nRecvNum = 0;//���ֽ�������
	char recvBuf[1024] = "";
	int recvBufLen = 1024;
	sockaddr_in addrClient = { 0 };
	int addrSize = sizeof(addrClient);
	char sendBuf[1024] = "";
	while (1) {
		//4.������--������Ϣ
		nRecvNum = recvfrom(sock, recvBuf, recvBufLen, 0, (SOCKADDR*)&addrClient, &addrSize);
		if (nRecvNum > 0) {//���յ���
			//��ӡ��������
			cout << "IP:" << inet_ntoa(addrClient.sin_addr) << "say:" << recvBuf << endl;
		}
		else if (nRecvNum == 0) {
			cout << "�����ѶϿ�" << endl;
			break;
		}
		else {
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			break;
		}

		//5.����������--������Ϣ
		/*gets_s(sendBuf);
		sendto(sock, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addrClient, addrSize);*/
	}

	
	//6.�°�ؼ�--�ر��׽��� ж�ؿ�
	err = closesocket(sock);
	if (err == SOCKET_ERROR) {
		printf("closesocket failed with error%u\n", WSAGetLastError());
	}
	WSACleanup();
	std::system("pause");
	return 0;

}