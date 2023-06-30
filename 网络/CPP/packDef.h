#pragma once
#include<memory>

//发送文件

//协议头
#define _DEF_PROTOCAL_BASE (1000)
//文件信息请求
#define _DEF_PROTOCAL_FILE_INFO_RQ (_DEF_PROTOCAL_BASE+1)
//文件块
#define _DEF_PROTOCAL__FILE_BLOCK_RQ (_DEF_PROTOCAL_BASE+2)

#define _DEF_MAX_FILE_PATH (512)
#define _DEF_FILE_CONTENT_SIZE (8*1024)

//协议结构体
//文件信息请求：协议头、文件名、文件大小、文件的唯一表示id
struct STRU_FILE_INFO_RQ {
	STRU_FILE_INFO_RQ():nType(_DEF_PROTOCAL_FILE_INFO_RQ),szFileSize(0){
		memset(szFileId, 0, _DEF_MAX_FILE_PATH);
		memset(szFileName, 0, _DEF_MAX_FILE_PATH);
	}
	int nType;
	char szFileId[_DEF_MAX_FILE_PATH];
	char szFileName[_DEF_MAX_FILE_PATH];
	long long szFileSize;//int:2G, long long:8G
};

//文件块:协议头、文件块、块大小、文件的唯一表示ID
struct STRU_FILE_BLOCK_RQ {
	STRU_FILE_BLOCK_RQ() :nType(_DEF_PROTOCAL__FILE_BLOCK_RQ), nBlockSize(0) {
		memset(szFileId, 0, _DEF_MAX_FILE_PATH);
		memset(szFileContent, 0, _DEF_FILE_CONTENT_SIZE);
	}
	int nType;
	char szFileId[_DEF_MAX_FILE_PATH];
	char szFileContent[_DEF_FILE_CONTENT_SIZE];
	int nBlockSize;
};


//文件信息：文件标志id、文件名、文件路径、当前位置、总大小、文件指针
struct FileIfo {
	FileIfo() :szFileSize(0), nPos(0), pFile(NULL){
		memset(szFileId, 0, _DEF_MAX_FILE_PATH);
		memset(szFileName, 0, _DEF_MAX_FILE_PATH);
		memset(szFilePath, 0, _DEF_MAX_FILE_PATH);
	}
	char szFilePath[_DEF_MAX_FILE_PATH];
	char szFileId[_DEF_MAX_FILE_PATH];
	char szFileName[_DEF_MAX_FILE_PATH];
	long long szFileSize;//文件总大小
	long long nPos;//文件在什么位置
	FILE* pFile;//文件指针
};