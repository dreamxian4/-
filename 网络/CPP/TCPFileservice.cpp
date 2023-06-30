#include<iostream>
#include<WinSock2.h>
#include"packDef.h"
#include<map>
#include<string>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")

//�����ļ�id���ļ���Ϣ��ӳ���ϵ
map<string, FileIfo*>m_mapIdToFileInfo;

//����������ݺ���
void DealData(SOCKET sock, char* buf, int nLen);
//�����ļ���Ϣ
void DealFileInfoRq(SOCKET sock, char* buf, int nLen);
//�����ļ���
void DealFileBlockRq(SOCKET sock, char* buf, int nLen);

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
	char recvBuf[1024*64] = "";

	int nPackSize = 0;

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
			//6.�Ƚ��հ���С
			nRecvNum = recv(sockClient, (char*)&nPackSize, sizeof(int), 0);
			if (nRecvNum > 0) {
				//�ٽ��հ�����
				nRecvNum = recv(sockClient, recvBuf, nPackSize, 0);
				if (nRecvNum > 0) {//���յ���
					//��ӡ��������
					//cout << "IP:" << inet_ntoa(addClient.sin_addr) << "say:" << recvBuf << endl;
					//�����������
					DealData(sockClient, recvBuf, nPackSize);
				}
			}
			else if (nRecvNum == 0) {
				cout << "�����ѶϿ�" << endl;
				break;
			}
			else {
				printf("recvfrom failed with error %d\n", WSAGetLastError());
				break;
			}
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

//����������ݺ���
void DealData(SOCKET sock, char* buf, int nLen) {
	//ȡ��Э��ͷ
	int nType = *(int*)buf;
	switch (nType) {
	case _DEF_PROTOCAL_FILE_INFO_RQ:
		DealFileInfoRq(sock, buf, nLen);
		break;
	case _DEF_PROTOCAL__FILE_BLOCK_RQ:
		DealFileBlockRq(sock, buf, nLen);
		break;
	default:break;
	}
}
//�����ļ���Ϣ
void DealFileInfoRq(SOCKET sock, char* buf, int nLen) {
	//1.���
	STRU_FILE_INFO_RQ* rq = (STRU_FILE_INFO_RQ*)buf;
	//2.�����ļ�������ڣ�ѡ�񱣴��ļ���·��
	char FILE_PATH[1024] = "";
	OPENFILENAMEA file = { 0 };
	file.lStructSize = sizeof(file);
	file.lpstrFilter = ("�����ļ�(*.*)\0*.*\0");//������
	file.lpstrFile = FILE_PATH;//�����ļ�����·���Ŀռ�
	file.nMaxFile = sizeof(FILE_PATH) / sizeof(*FILE_PATH);//�ռ����д����ַ���
	file.Flags = OFN_EXPLORER;
	strcpy_s(file.lpstrFile, 1024, rq->szFileName);//���.exeͬ��
	BOOL flag = GetSaveFileNameA(&file);
	if (FALSE == flag) {
		//�û�û�и�����·�����͸�һ��Ĭ�ϵı���·��
		strcpy_s(file.lpstrFile, 1024, rq->szFileName);//���.exeͬ��
	}
	//3.����filelfo��Ϊ�����ļ�����׼��
	FileIfo* info=new FileIfo;
	info->szFileSize = rq->szFileSize;
	info->nPos = 0;
	strcpy_s(info->szFileId, rq->szFileId);
	strcpy_s(info->szFileName, rq->szFileName);
	strcpy_s(info->szFilePath, file.lpstrFile);

	fopen_s(&info->pFile, info->szFilePath, "wb");

	cout << info->szFileId << endl;
	cout << info->szFileName << endl;
	cout << info->szFilePath << endl;
	cout << info->szFileSize << endl;

	//4.filelfo������map��
	if (m_mapIdToFileInfo.count(info->szFileId) <= 0) {
		m_mapIdToFileInfo[info->szFileId] = info;
	}
}
//�����ļ���
void DealFileBlockRq(SOCKET sock, char* buf, int nLen) {
	//1.���
	STRU_FILE_BLOCK_RQ* rq = (STRU_FILE_BLOCK_RQ*)buf;
	//2.�����ļ�IDȡ���ļ���Ϣ
	if (m_mapIdToFileInfo.count(rq->szFileId) <= 0) {
		return;
	}
	FileIfo* info = m_mapIdToFileInfo[rq->szFileId];
	int nRes = fwrite(rq->szFileContent, 1, rq->nBlockSize, info->pFile);
	info->nPos += nRes;
	cout << info->nPos << endl;
	//3.�ļ�д��
	if (info->nPos >= info->szFileSize) {
		//�ر��ļ����
		fclose(info->pFile);
		//map�нڵ�ɾ�������տռ�
		m_mapIdToFileInfo.erase(info->szFileId);
		delete info;
		info = NULL;
	}
}