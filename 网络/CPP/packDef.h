#pragma once
#include<memory>

//�����ļ�

//Э��ͷ
#define _DEF_PROTOCAL_BASE (1000)
//�ļ���Ϣ����
#define _DEF_PROTOCAL_FILE_INFO_RQ (_DEF_PROTOCAL_BASE+1)
//�ļ���
#define _DEF_PROTOCAL__FILE_BLOCK_RQ (_DEF_PROTOCAL_BASE+2)

#define _DEF_MAX_FILE_PATH (512)
#define _DEF_FILE_CONTENT_SIZE (8*1024)

//Э��ṹ��
//�ļ���Ϣ����Э��ͷ���ļ������ļ���С���ļ���Ψһ��ʾid
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

//�ļ���:Э��ͷ���ļ��顢���С���ļ���Ψһ��ʾID
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


//�ļ���Ϣ���ļ���־id���ļ������ļ�·������ǰλ�á��ܴ�С���ļ�ָ��
struct FileIfo {
	FileIfo() :szFileSize(0), nPos(0), pFile(NULL){
		memset(szFileId, 0, _DEF_MAX_FILE_PATH);
		memset(szFileName, 0, _DEF_MAX_FILE_PATH);
		memset(szFilePath, 0, _DEF_MAX_FILE_PATH);
	}
	char szFilePath[_DEF_MAX_FILE_PATH];
	char szFileId[_DEF_MAX_FILE_PATH];
	char szFileName[_DEF_MAX_FILE_PATH];
	long long szFileSize;//�ļ��ܴ�С
	long long nPos;//�ļ���ʲôλ��
	FILE* pFile;//�ļ�ָ��
};