#include<iostream>
#include"CMySql.h"
using namespace std;

struct student {
	string no;
	string name;
	string sex;
	string age;
};

int main() {
	CMySql sql;
	//�������ݿ�
	if (!sql.ConnectMySql("127.0.0.1","root","123456","myfirst1216")) {
		cout << "���ݿ��ʧ��" << endl;
		system("pause");
		return 0;
	}
	//��ѯ���ݿ�
	list<string>lstRes;
	char sqlBuf[1024] = "";
	sprintf_s(sqlBuf, "select * from studentinfo;");
	if (!sql.SelectMysel(sqlBuf,4,lstRes)) {
		cout << "select errer��" << sqlBuf << endl;
	}
	struct student stu{};
	while (lstRes.size() > 0) {
		stu.no = lstRes.front();
		lstRes.pop_front();

		stu.name = lstRes.front();
		lstRes.pop_front();

		stu.sex = lstRes.front();
		lstRes.pop_front();

		stu.age = lstRes.front();
		lstRes.pop_front();

		cout <<"number:" << stu.no.c_str()<< 
			";name:" << stu.name.c_str() << 
			";sex:" << stu.sex.c_str() << 
			";age:" << stu.age.c_str() << endl;
	}

	//�������ݿ�����
	//����
	char ins[1024] = "";
	sprintf(ins, "insert into studentinfo values('100','ë����','��','30');");
	if (!sql.UpdateMySql(ins)) {
		cout << "update errer:" << ins << endl;
	}
	
	//����
	char upd[1024] = "";
	sprintf(upd, "update studentinfo set name='����' where S='50';");
	if (!sql.UpdateMySql(upd)) {
		cout << "update errer:" << upd << endl;
	}
	
	//ɾ��
	char del[1024] = "";
	sprintf(del, "delete from studentinfo where S='100';");
	if (!sql.UpdateMySql(del)) {
		cout << "update errer:" << del << endl;
	}
	
	//�Ͽ����ݿ�����
	system("pause");
	sql.DisConnect();
	return 0;
}