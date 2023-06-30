#include<iostream>
#include<Windows.h>
using namespace std;

//�ؼ��ΰ�װ CRITICAL_SECTION
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

//������
mylock ml;

int ncount = 0;
//TODO:�̺߳�������ͬһ������count++100��
DWORD WINAPI thread01(LPVOID IpParameter) {
	int a = 100;
	while (a--) {
		//����
		ml.lock();
		cout << ncount++ << " ";
		//����
		ml.unlock();
		Sleep(10);
	}
	return 0;
}

int main() {

	//TODO:����3���߳�
	HANDLE hand1=CreateThread(NULL, 0, &thread01, (void*)0, 0, NULL);
	HANDLE hand2=CreateThread(NULL, 0, &thread01, (void*)0, 0, NULL);
	HANDLE hand3=CreateThread(NULL, 0, &thread01, (void*)0, 0, NULL);

	//�˳��߳�
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