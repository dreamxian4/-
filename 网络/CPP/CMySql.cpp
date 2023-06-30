#include"CMySql.h"


CMySql::CMySql(void) {
	m_sock = new MYSQL;
	//初始化数据库
	mysql_init(m_sock);
	//设置字符编码
	mysql_set_character_set(m_sock, "gb2312");
	//mysql_options(m_sock, MYSQL_SET_CHARSET_NAME, "gbk");
}

CMySql::~CMySql(void) {
	if (m_sock) {
		delete m_sock;
		m_sock = NULL;
	}
}

void CMySql::DisConnect() {
	mysql_close(m_sock);
}

bool CMySql::ConnectMySql(char* host, char* user, char* pass, char* db) {
	if (mysql_real_connect(m_sock, host, user, pass, db, 3306, NULL, 0) == NULL) {
		return false;
	}
	return true;
}

bool CMySql::SelectMysel(char* szSql, int nColumn, list<string>& lstStr) {
	//查询数据：返回0，说明成功了
	int ret = mysql_query(m_sock, szSql);
	//获取结果集
	m_results = mysql_store_result(m_sock);
	//给ROW赋值
	while (m_record = mysql_fetch_row(m_results)) {
		for (int i = 0; i < nColumn; i++) {
			if(m_record[i])
			lstStr.push_back(m_record[i]);
			else lstStr.push_back("");
		}
	}
	return true;
}

bool CMySql::UpdateMySql(char* szSql) {
	int ret = mysql_query(m_sock, szSql);
	return !ret;
}
