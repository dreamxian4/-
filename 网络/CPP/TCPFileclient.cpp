#include<iostream>
#include<WinSock2.h>
#include"packDef.h"

using namespace std;
#pragma comment(lib,"Ws2_32.lib")

//发送文件
void SendFile(SOCKET sock);
//获取文件名称
string getFileName(char* path);
//发送函数
void senddATA(SOCKET sock, char* buf, int nLen);

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

	//发送
	do {
		SendFile(sock);
	} while (0);

	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}

//获取文件名称
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
	//1.读取文件信息
	char FILE_PATH[1024] = "";
	OPENFILENAMEA file = { 0 };
	file.lStructSize = sizeof(file);
	file.lpstrFilter = ("所有文件(*.*)\0*.*\0文本(*.txt)\0*.txt\0");//过滤器
	file.lpstrFile = FILE_PATH;//保存文件完整路径的空间
	file.nMaxFile = sizeof(FILE_PATH) / sizeof(*FILE_PATH);//空间可以写入的字符数
	file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	BOOL flag = GetOpenFileNameA(&file);
	if (FALSE == flag) {
		return;
	}
	cout << file.lpstrFile << endl;//输出结果：文件完整路径


	//2.发送文件信息请求
	STRU_FILE_INFO_RQ rq;
	string name = getFileName(file.lpstrFile);
	strcpy_s(rq.szFileName, _DEF_MAX_FILE_PATH,name.c_str());
	cout << rq.szFileName << endl;

	//获取系统时间
	SYSTEMTIME time;
	GetLocalTime(&time);
	sprintf(rq.szFileId, "%s_%02d_%02d_%02d_%02d", 
		rq.szFileName, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	cout << rq.szFileId << endl;

	//获取文件大小
	FILE* pFile = NULL;
	fopen_s(&pFile, file.lpstrFile, "rb");
	fseek(pFile,0,SEEK_END);//将光标移到文件末尾
	rq.szFileSize=_ftelli64(pFile);//64为操作系统_ftelli64，32位_ftell
	fseek(pFile, 0, SEEK_SET);//将光标移到文件开头
	cout << rq.szFileSize << endl;

	senddATA(sock, (char*)&rq, sizeof(rq));

	//3.发送文件块
	STRU_FILE_BLOCK_RQ blockRq;
	long long nPos = 0;
	int nReadLen = 0;
	while (1) {
		nReadLen = fread(blockRq.szFileContent, 1, _DEF_FILE_CONTENT_SIZE, pFile);
		blockRq.nBlockSize = nReadLen;
		strcpy(blockRq.szFileId, rq.szFileId);
		senddATA(sock, (char*)&blockRq, sizeof(blockRq));
		nPos += nReadLen;
		if (nPos>=rq.szFileSize|| nReadLen< _DEF_FILE_CONTENT_SIZE) {//触发退出条件
			fclose(pFile);
			break;
		}
		Sleep(1);
	}
}

//发送函数
void senddATA(SOCKET sock, char* buf, int nLen) {
	//先发包大小（防止粘包）
	send(sock, (char*)&nLen, sizeof(int), 0);
	//再发包内容
	send(sock, (char*)buf, nLen, 0);
}