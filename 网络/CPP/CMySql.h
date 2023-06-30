#pragma once

#include<mysql.h>

#pragma comment(lib,"libmysql.lib")

#include<list>
#include<string>
using namespace std;

class CMySql {
public:
	CMySql(void);
	~CMySql(void);
public:					//ip,�û��������룬���ݿ⣬�˿ں�
	bool ConnectMySql(char* host, char* user, char* pass, char* db);
	void DisConnect();
	bool SelectMysel(char* szSql, int nColumn, list<string>& lstStr);
	//������ݿ��еı�
	bool GetTables(char* szSql,list<string>&lstStr);
	//���£�ɾ�������롢�޸�
	bool UpdateMySql(char* szSql);
private:
	MYSQL* m_sock;//���ݿ���
	MYSQL_RES* m_results;//��ѯ�����
	MYSQL_ROW m_record;//��¼�ṹ��
};