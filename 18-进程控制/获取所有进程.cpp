#include <windows.h>
#include <tlhelp32.h>	//声明快照头文件
#include <iostream>
using namespace std;

int main() {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hpsnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	//当前所有进程快照
	if (hpsnap == INVALID_HANDLE_VALUE) {
		cout << "CreateToolhelp32Snapshot失败" << endl;
		return -1;
	}

	BOOL bnext = ::Process32First(hpsnap, &pe32);	//遍历当前进程快照
	while (bnext) {
		cout << "进程名称:" << pe32.szExeFile << endl;
		cout << "进程ID号:" << pe32.th32ProcessID << endl << endl;
		bnext = ::Process32Next(hpsnap, &pe32);
	}

	::CloseHandle(hpsnap);

	return 0;
}
