#include<iostream>
#include<Windows.h>
using namespace std;

bool quit = false;

//�̺߳���--׬Ǯ
DWORD WINAPI ThreadProc01(LPVOID IpParameter) {

	//���Զ��˳����̣߳�forѭ����������߳̽���
	long count = (long)IpParameter;
	for (int i = 1; i <= count; i++) {
		cout << "׬��" << i << "Ԫ" << endl;
		Sleep(100);
	}

	//�����Զ��˳�
	/*while (!quit) {
		Sleep(100);
		while (1) {
			Sleep(100);
			cout << 1;
		}
	}*/

	return 0;
}

//������Ҳ��һ���߳�
int main() {

	//�������̺߳�����ִ��
	//HANDLE hand = CreateThread(NULL,//��ȫ��������
	//	0,//�߳�ջ��С��Ĭ��1MB
	//	&ThreadProc01,//�̺߳����ĵ�ַ
	//	(VOID*)80,//�̺߳����Ĳ���
	//	0,//�����̵߳ĳ�ʼ״̬��0������ִ�У�
	//	NULL//�߳�ID
	//);

	//�������̺߳����
	HANDLE hand = CreateThread(NULL,//��ȫ��������
		0,//�߳�ջ��С��Ĭ��1MB
		&ThreadProc01,//�̺߳����ĵ�ַ
		(VOID*)80,//�̺߳����Ĳ���
		CREATE_SUSPENDED,//�����̵߳ĳ�ʼ״̬��0������ִ�У�
		NULL//�߳�ID
	);

	//������˯���߳�
	int i = 0;
	while (1) {
		Sleep(1000);//��ms����˯��
		i++;
		cout << "˯��" << i << "��" << endl;
		if (i == 10)break;

		if (i == 3) {//�������ָ̻߳�
			ResumeThread(hand);
		}

		if (i == 4)SuspendThread(hand);
		if (i == 5)ResumeThread(hand);
		if (i == 6) {
			//�߳��˳�
			if (hand) {//�ж��߳��Ƿ����
				quit = true;//ͨ����־λ��ѭ���˳�
				if (WaitForSingleObject(hand, 100) == WAIT_TIMEOUT) {//�ȴ�100ms�����̻߳��ڣ���ǿ��ɱ���߳�
					TerminateThread(hand, -1);//�˳��̣߳�-1��ʾ�쳣�˳�
					CloseHandle(hand);//�رվ��
					hand = NULL;
				}
			}
		}
	}
	cout << "˯����" << endl;
	system("pause");
	return 0;
}