#include<iostream>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

int main() {
	//1.ѡ��Ŀ--���ؿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);//2.2�汾��
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {//err����0��˵�����سɹ�
		printf("WSAStartup failed with error:%d\n", err);
		std::system("pause");
		return 1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {//�жϰ汾���Ƿ�Ϊ2.2
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();//ж�ؿ�
		std::system("pause");
		return 1;
	}

	//2.����--�����׽���
	SOCKET sock = INVALID_SOCKET;//�Ƿ�
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//���������ֱ����ipv4��ַ ʹ��udpЭ�� UDPЭ��
	if (sock == INVALID_SOCKET) {//��������Ȼ�Ƿ�
		printf("socket function failed with error=%d\n", WSAGetLastError());//��ӡ�����루����->�������->��������룩
		WSACleanup();//ж�ؿ�
		std::system("pause");
		return 1;
	}
	else {
		printf("socket function succeeded\n");
	}

	//�������˵�IP��ַ�����䷢����Ϣ
	sockaddr_in addrservice;
	addrservice.sin_family = AF_INET;
	addrservice.sin_addr.s_addr = inet_addr("192.168.244.1");//�������˵�IP��ַ
	addrservice.sin_port = htons(12345);//�˿ں�
	int addrSize = sizeof(addrservice);

	char sendBuf[1024] = "";//���͵�����
	int nRecvNum = 0;//���ֽ�������
	char recvBuf[1024] = "";
	int recvBufLen = 1024;
	while (1) {
		//3.������--������Ϣ
		gets_s(sendBuf);
		sendto(sock, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addrservice, addrSize);

		//4.ȡ��--������Ϣ
		nRecvNum = recvfrom(sock, recvBuf, recvBufLen, 0, 0, 0);//�Լ��������͵ģ�����Ҫ���շ������˵�IP��ַ
		if (nRecvNum > 0) {//���յ���
			//��ӡ��������
			cout << "������: " << recvBuf << endl;
		}
		else if (nRecvNum == 0) {
			cout << "�����ѶϿ�" << endl;
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

	//6.�°�ؼ�--�ر��׽��� ж�ؿ�
	err = closesocket(sock);
	if (err == SOCKET_ERROR) {
		printf("closesocket failed with error%u\n", WSAGetLastError());
	}
	WSACleanup();
	std::system("pause");
	return 0;
}