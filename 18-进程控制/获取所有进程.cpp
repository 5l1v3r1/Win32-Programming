#include <windows.h>
#include <tlhelp32.h>	//��������ͷ�ļ�
#include <iostream>
using namespace std;

int main() {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hprocesssnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	//��ǰ���н��̿���
	if (hprocesssnap == INVALID_HANDLE_VALUE) {
		cout << "CreateToolhelp32Snapshotʧ��" << endl;
		return -1;
	}

	BOOL bnext = ::Process32First(hprocesssnap, &pe32);	//������ǰ���̿���
	while (bnext) {
		cout << "��������:" << pe32.szExeFile << endl;
		cout << "����ID��:" << pe32.th32ProcessID << endl << endl;
		bnext = ::Process32Next(hprocesssnap, &pe32);
	}

	::CloseHandle(hprocesssnap);

	return 0;
}