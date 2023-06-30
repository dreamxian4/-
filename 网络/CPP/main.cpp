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
	//连接数据库
	if (!sql.ConnectMySql("127.0.0.1","root","123456","myfirst1216")) {
		cout << "数据库打开失败" << endl;
		system("pause");
		return 0;
	}
	//查询数据库
	list<string>lstRes;
	char sqlBuf[1024] = "";
	sprintf_s(sqlBuf, "select * from studentinfo;");
	if (!sql.SelectMysel(sqlBuf,4,lstRes)) {
		cout << "select errer：" << sqlBuf << endl;
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

	//更新数据库数据
	//插入
	char ins[1024] = "";
	sprintf(ins, "insert into studentinfo values('100','毛不爱','男','30');");
	if (!sql.UpdateMySql(ins)) {
		cout << "update errer:" << ins << endl;
	}
	
	//更新
	char upd[1024] = "";
	sprintf(upd, "update studentinfo set name='狗狗' where S='50';");
	if (!sql.UpdateMySql(upd)) {
		cout << "update errer:" << upd << endl;
	}
	
	//删除
	char del[1024] = "";
	sprintf(del, "delete from studentinfo where S='100';");
	if (!sql.UpdateMySql(del)) {
		cout << "update errer:" << del << endl;
	}
	
	//断开数据库连接
	system("pause");
	sql.DisConnect();
	return 0;
}