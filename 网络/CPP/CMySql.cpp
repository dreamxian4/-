#include"CMySql.h"


CMySql::CMySql(void) {
	m_sock = new MYSQL;
	//��ʼ�����ݿ�
	mysql_init(m_sock);
	//�����ַ�����
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
	//��ѯ���ݣ�����0��˵���ɹ���
	int ret = mysql_query(m_sock, szSql);
	//��ȡ�����
	m_results = mysql_store_result(m_sock);
	//��ROW��ֵ
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
