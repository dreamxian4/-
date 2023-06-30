#include<iostream>
#include<Windows.h>
using namespace std;

//关键段包装 CRITICAL_SECTION
class mylock {
private:
	CRITICAL_SECTION cs;
public:
	mylock() {
		InitializeCriticalSection(&cs);
	}
	~mylock() {
		DeleteCriticalSection(&cs);
	}
	void lock() {
		EnterCriticalSection(&cs);
	}
	void unlock() {
		LeaveCriticalSection(&cs);
	}
};

//锁对象
mylock ml;

int ncount = 0;
//TODO:线程函数：对同一个变量count++100次
DWORD WINAPI thread01(LPVOID IpParameter) {
	int a = 100;
	while (a--) {
		//加锁
		ml.lock();
		cout << ncount++ << " ";
		//开锁
		ml.unlock();
		Sleep(10);
	}
	return 0;
}

int main() {

	//TODO:创建3个线程
	HANDLE hand1=CreateThread(NULL, 0, &thread01, (void*)0, 0, NULL);
	HANDLE hand2=CreateThread(NULL, 0, &thread01, (void*)0, 0, NULL);
	HANDLE hand3=CreateThread(NULL, 0, &thread01, (void*)0, 0, NULL);

	//退出线程
	if (WaitForSingleObject(hand1, 10000) == WAIT_TIMEOUT) {
		TerminateThread(hand1,-1);
		CloseHandle(hand1);
		hand1 = NULL;
	}
	if (WaitForSingleObject(hand2, 10000) == WAIT_TIMEOUT) {
		TerminateThread(hand2, -1);
		CloseHandle(hand2);
		hand2 = NULL;
	}
	if (WaitForSingleObject(hand3, 10000) == WAIT_TIMEOUT) {
		TerminateThread(hand3, -1);
		CloseHandle(hand3);
		hand3 = NULL;
	}

	system("pause");
	return 0;
}