#include <windows.h>
#include <iostream>
using namespace std;

typedef HANDLE (WINAPI* OldOpenProcess)(DWORD, BOOL, DWORD);	//ԭAPI��ַ
OldOpenProcess openprocess=NULL;	//ָ��ԭ������ָ��  
FARPROC pfOldOpenProcess=NULL;  //ָ������Զָ��

HANDLE WINAPI fakeOpenProcess(DWORD, BOOL, DWORD )  {		//��API����
	::MessageBox(NULL, "123", "123", MB_OK);
    return NULL;
}  

void getapi() {		//��ȡԭAPI��ַ
	  HMODULE hmodule=::LoadLibrary("kernel32.dll");
	  openprocess=(OldOpenProcess)::GetProcAddress(hmodule, "OpenProcess");  
	  pfOldOpenProcess=(FARPROC)openprocess; 
}

BYTE OldCode[5];
BYTE NewCode[5]; 
void savecode() {
	_asm  {		// ��ԭAPI�����ǰ5���ֽڴ��뱣�浽OldCode[]  
		lea edi,OldCode //��ȡOldCode����ĵ�ַ,�ŵ�edi  
		mov esi,pfOldOpenProcess //��ȡԭAPI��ڵ�ַ���ŵ�esi  
		cld    //�����־λ��Ϊ��������ָ����׼��  
		movsd //����ԭAPI���ǰ4���ֽڵ�OldCode����  
		movsb //����ԭAPI��ڵ�5���ֽڵ�OldCode����  
	}

	_asm  {	//��ȡfakeOpenProcess����Ե�ַ,ΪJmp��׼��,5���ֽ� 
		lea eax,fakeOpenProcess //��ȡ��API��fakeOpenProcess������ַ  
		mov ebx,pfOldOpenProcess  //ԭϵͳAPI������ַ  
		sub eax,ebx           //int nAddr = UserFunAddr - SysFunAddr  
		sub eax,5             //nAddr=nAddr-5  
		mov dword ptr [NewCode+1],eax //һ��������ַռ4���ֽ�,������ĵ�ַnAddr���浽NewCode����4���ֽ�
	}
	NewCode[0]=0xe9; //NewCode��һ���ֽ�ΪJMP
}

void hookapi() {
	DWORD dwTemp=0;  
	DWORD dwOldProtect=0;
	DWORD dwPid=::GetCurrentProcessId();
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,0,dwPid);
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, PAGE_READWRITE, &dwOldProtect);    //�ı��������ڴ�����ı�������
	WriteProcessMemory(hProcess, pfOldOpenProcess, NewCode, 5, 0);  //�޸�API�������ǰ5���ֽ�Ϊjmp xxxxxx  
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, dwOldProtect, &dwTemp);  
}

void test() {
    HWND h = ::FindWindow(NULL, "C:\Documents and Settings\Administrator\����\hookapi\Debug\1.exe");  //  Ѱ�Ҳ��򿪽���
    DWORD processid = 0;
    GetWindowThreadProcessId(h, &processid);
    HANDLE hprocess = 0;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
}

void unhookapi() {   
	DWORD dwTemp=0;  
	DWORD dwOldProtect=0;
	DWORD dwPid=::GetCurrentProcessId();
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,0,dwPid);
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, PAGE_READWRITE, &dwOldProtect);    //�ı��������ڴ�����ı�������
	WriteProcessMemory(hProcess, pfOldOpenProcess, OldCode, 5, 0);  //�޸�API�������ǰ5���ֽ�Ϊjmp xxxxxx  
	VirtualProtectEx(hProcess, pfOldOpenProcess, 5, dwOldProtect, &dwTemp);     
}  

int main() {
	getapi();
	savecode();
	unhookapi();
	hookapi();
	test();
	unhookapi();
	test();
	return 0;

}