#define _WIN32_WINNT 0x0400	//Windows NT 4.0
#include <windows.h>
#include <iostream>
using namespace std;

MSG msg;
HHOOK mhook=NULL;

LRESULT WINAPI KeyProc(int code,WPARAM wParam,LPARAM lParam) {
	LPKBDLLHOOKSTRUCT p=(LPKBDLLHOOKSTRUCT)lParam;
	if(code<0)
		CallNextHookEx(0,code,wParam,lParam);
	if(code==HC_ACTION) {
		//���� ALT+F4
		if((p->vkCode==VK_F4)&&((p->flags&0x20)>0))
			return 1;
	}
	CallNextHookEx(0,code,wParam,lParam);
	return 0;
}

void messageloop() {	//��Ϣѭ�������ϴ�����Ϣ,(mfc�������Ѱ����ɲ���,C++����̨������ʹ��)	
while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	};
}

void sethook() {	//��������
	mhook=::SetWindowsHookEx(WH_KEYBOARD_LL,KeyProc,GetModuleHandle(NULL),0);
	if(mhook)
		cout << "�Ѿ�����win��" << endl;
}


int main()  {
	sethook();
	messageloop();
	return 0;
};
