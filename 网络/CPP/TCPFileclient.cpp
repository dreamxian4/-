#include<iostream>
#include<WinSock2.h>
#include"packDef.h"

using namespace std;
#pragma comment(lib,"Ws2_32.lib")

//�����ļ�
void SendFile(SOCKET sock);
//��ȡ�ļ�����
string getFileName(char* path);
//���ͺ���
void senddATA(SOCKET sock, char* buf, int nLen);

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

	//����
	do {
		SendFile(sock);
	} while (0);

	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}

//��ȡ�ļ�����
string getFileName(char* path) {
	if (!path) {
		return string();
	}
	int nLen = strlen(path);
	if (nLen < 1) {
		return string();
	}
	for (int i = nLen - 1; i >= 0; i--) {
		if ('\\' == path[i] || '/' == path[i]) {
			return &path[i + 1];
		}
	}
	return string();
}

void SendFile(SOCKET sock) {
	//1.��ȡ�ļ���Ϣ
	char FILE_PATH[1024] = "";
	OPENFILENAMEA file = { 0 };
	file.lStructSize = sizeof(file);
	file.lpstrFilter = ("�����ļ�(*.*)\0*.*\0�ı�(*.txt)\0*.txt\0");//������
	file.lpstrFile = FILE_PATH;//�����ļ�����·���Ŀռ�
	file.nMaxFile = sizeof(FILE_PATH) / sizeof(*FILE_PATH);//�ռ����д����ַ���
	file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	BOOL flag = GetOpenFileNameA(&file);
	if (FALSE == flag) {
		return;
	}
	cout << file.lpstrFile << endl;//���������ļ�����·��


	//2.�����ļ���Ϣ����
	STRU_FILE_INFO_RQ rq;
	string name = getFileName(file.lpstrFile);
	strcpy_s(rq.szFileName, _DEF_MAX_FILE_PATH,name.c_str());
	cout << rq.szFileName << endl;

	//��ȡϵͳʱ��
	SYSTEMTIME time;
	GetLocalTime(&time);
	sprintf(rq.szFileId, "%s_%02d_%02d_%02d_%02d", 
		rq.szFileName, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	cout << rq.szFileId << endl;

	//��ȡ�ļ���С
	FILE* pFile = NULL;
	fopen_s(&pFile, file.lpstrFile, "rb");
	fseek(pFile,0,SEEK_END);//������Ƶ��ļ�ĩβ
	rq.szFileSize=_ftelli64(pFile);//64Ϊ����ϵͳ_ftelli64��32λ_ftell
	fseek(pFile, 0, SEEK_SET);//������Ƶ��ļ���ͷ
	cout << rq.szFileSize << endl;

	senddATA(sock, (char*)&rq, sizeof(rq));

	//3.�����ļ���
	STRU_FILE_BLOCK_RQ blockRq;
	long long nPos = 0;
	int nReadLen = 0;
	while (1) {
		nReadLen = fread(blockRq.szFileContent, 1, _DEF_FILE_CONTENT_SIZE, pFile);
		blockRq.nBlockSize = nReadLen;
		strcpy(blockRq.szFileId, rq.szFileId);
		senddATA(sock, (char*)&blockRq, sizeof(blockRq));
		nPos += nReadLen;
		if (nPos>=rq.szFileSize|| nReadLen< _DEF_FILE_CONTENT_SIZE) {//�����˳�����
			fclose(pFile);
			break;
		}
		Sleep(1);
	}
}

//���ͺ���
void senddATA(SOCKET sock, char* buf, int nLen) {
	//�ȷ�����С����ֹճ����
	send(sock, (char*)&nLen, sizeof(int), 0);
	//�ٷ�������
	send(sock, (char*)buf, nLen, 0);
}