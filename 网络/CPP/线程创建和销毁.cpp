#include<iostream>
#include<Windows.h>
using namespace std;

bool quit = false;

//线程函数--赚钱
DWORD WINAPI ThreadProc01(LPVOID IpParameter) {

	//可自动退出的线程：for循环结束后该线程结束
	long count = (long)IpParameter;
	for (int i = 1; i <= count; i++) {
		cout << "赚了" << i << "元" << endl;
		Sleep(100);
	}

	//不能自动退出
	/*while (!quit) {
		Sleep(100);
		while (1) {
			Sleep(100);
			cout << 1;
		}
	}*/

	return 0;
}

//主函数也是一个线程
int main() {

	//创建出线程后立即执行
	//HANDLE hand = CreateThread(NULL,//安全级别描述
	//	0,//线程栈大小，默认1MB
	//	&ThreadProc01,//线程函数的地址
	//	(VOID*)80,//线程函数的参数
	//	0,//创建线程的初始状态（0：立即执行）
	//	NULL//线程ID
	//);

	//创建出线程后挂起
	HANDLE hand = CreateThread(NULL,//安全级别描述
		0,//线程栈大小，默认1MB
		&ThreadProc01,//线程函数的地址
		(VOID*)80,//线程函数的参数
		CREATE_SUSPENDED,//创建线程的初始状态（0：立即执行）
		NULL//线程ID
	);

	//主函数睡觉线程
	int i = 0;
	while (1) {
		Sleep(1000);//以ms级别睡眠
		i++;
		cout << "睡了" << i << "秒" << endl;
		if (i == 10)break;

		if (i == 3) {//将挂起线程恢复
			ResumeThread(hand);
		}

		if (i == 4)SuspendThread(hand);
		if (i == 5)ResumeThread(hand);
		if (i == 6) {
			//线程退出
			if (hand) {//判断线程是否存在
				quit = true;//通过标志位让循环退出
				if (WaitForSingleObject(hand, 100) == WAIT_TIMEOUT) {//等待100ms，若线程还在，就强制杀死线程
					TerminateThread(hand, -1);//退出线程，-1表示异常退出
					CloseHandle(hand);//关闭句柄
					hand = NULL;
				}
			}
		}
	}
	cout << "睡醒了" << endl;
	system("pause");
	return 0;
}