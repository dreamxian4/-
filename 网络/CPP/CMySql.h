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
public:					//ip,用户名，密码，数据库，端口号
	bool ConnectMySql(char* host, char* user, char* pass, char* db);
	void DisConnect();
	bool SelectMysel(char* szSql, int nColumn, list<string>& lstStr);
	//获得数据库中的表
	bool GetTables(char* szSql,list<string>&lstStr);
	//更新：删除、插入、修改
	bool UpdateMySql(char* szSql);
private:
	MYSQL* m_sock;//数据库句柄
	MYSQL_RES* m_results;//查询结果集
	MYSQL_ROW m_record;//记录结构体
};