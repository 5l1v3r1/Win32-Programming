#include <windows.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {

	HANDLE hobj = ::CreateMutex(NULL, false, "test-object");

	if (::GetLastError() == ERROR_ALREADY_EXISTS) {
		::MessageBox(NULL, "�������ж��ʵ��", "����", MB_OK);
		exit(0);
	}

	while (1) {
		cout << "����������." << endl;
		::Sleep(1000);
		system("cls");
		cout << "����������.." << endl;
		::Sleep(1000);
		system("cls");
		cout << "����������..." << endl;
		::Sleep(1000);
		system("cls");
	}

	::CloseHandle(hobj);

	return 0;
}