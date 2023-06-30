#include<iostream>
#include<WinSock2.h>
#include"packDef.h"
#include<map>
#include<string>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")

//保存文件id和文件信息的映射关系
map<string, FileIfo*>m_mapIdToFileInfo;

//处理接收数据函数
void DealData(SOCKET sock, char* buf, int nLen);
//处理文件信息
void DealFileInfoRq(SOCKET sock, char* buf, int nLen);
//处理文件块
void DealFileBlockRq(SOCKET sock, char* buf, int nLen);

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
			//6.先接收包大小
			nRecvNum = recv(sockClient, (char*)&nPackSize, sizeof(int), 0);
			if (nRecvNum > 0) {
				//再接收包内容
				nRecvNum = recv(sockClient, recvBuf, nPackSize, 0);
				if (nRecvNum > 0) {//接收到了
					//打印接收数据
					//cout << "IP:" << inet_ntoa(addClient.sin_addr) << "say:" << recvBuf << endl;
					//处理接收数据
					DealData(sockClient, recvBuf, nPackSize);
				}
			}
			else if (nRecvNum == 0) {
				cout << "连接已断开" << endl;
				break;
			}
			else {
				printf("recvfrom failed with error %d\n", WSAGetLastError());
				break;
			}
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

//处理接收数据函数
void DealData(SOCKET sock, char* buf, int nLen) {
	//取出协议头
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
//处理文件信息
void DealFileInfoRq(SOCKET sock, char* buf, int nLen) {
	//1.拆包
	STRU_FILE_INFO_RQ* rq = (STRU_FILE_INFO_RQ*)buf;
	//2.弹出文件浏览窗口，选择保存文件的路径
	char FILE_PATH[1024] = "";
	OPENFILENAMEA file = { 0 };
	file.lStructSize = sizeof(file);
	file.lpstrFilter = ("所有文件(*.*)\0*.*\0");//过滤器
	file.lpstrFile = FILE_PATH;//保存文件完整路径的空间
	file.nMaxFile = sizeof(FILE_PATH) / sizeof(*FILE_PATH);//空间可以写入的字符数
	file.Flags = OFN_EXPLORER;
	strcpy_s(file.lpstrFile, 1024, rq->szFileName);//相对.exe同级
	BOOL flag = GetSaveFileNameA(&file);
	if (FALSE == flag) {
		//用户没有给保存路径，就给一个默认的保存路径
		strcpy_s(file.lpstrFile, 1024, rq->szFileName);//相对.exe同级
	}
	//3.保存filelfo，为接收文件块做准备
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

	//4.filelfo保存在map中
	if (m_mapIdToFileInfo.count(info->szFileId) <= 0) {
		m_mapIdToFileInfo[info->szFileId] = info;
	}
}
//处理文件块
void DealFileBlockRq(SOCKET sock, char* buf, int nLen) {
	//1.拆包
	STRU_FILE_BLOCK_RQ* rq = (STRU_FILE_BLOCK_RQ*)buf;
	//2.根据文件ID取出文件信息
	if (m_mapIdToFileInfo.count(rq->szFileId) <= 0) {
		return;
	}
	FileIfo* info = m_mapIdToFileInfo[rq->szFileId];
	int nRes = fwrite(rq->szFileContent, 1, rq->nBlockSize, info->pFile);
	info->nPos += nRes;
	cout << info->nPos << endl;
	//3.文件写完
	if (info->nPos >= info->szFileSize) {
		//关闭文件句柄
		fclose(info->pFile);
		//map中节点删除，回收空间
		m_mapIdToFileInfo.erase(info->szFileId);
		delete info;
		info = NULL;
	}
}