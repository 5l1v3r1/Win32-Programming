#include <windows.h>
#include <iostream>
using namespace std;

typedef HANDLE (WINAPI* OldOpenProcess)(DWORD, BOOL, DWORD);	//ԭAPI��ַ
OldOpenProcess openprocess=NULL;	//ָ��ԭ������ָ��  
FARPROC pfOldOpenProcess=NULL;  //ָ������Զָ��
BYTE OldCode[5];	//ԭ����ǰ5�ֽ�  
BYTE NewCode[5]; 	//�ٺ���ǰ5�ֽ�  
HANDLE hprocess;	//���̾�� 
HANDLE hprocess2;	//������̾������
void unhookapi();
void hookapi();


HANDLE WINAPI fakeOpenProcess(DWORD, BOOL, DWORD )  {		//��API����
	unhookapi();
	//��ΪMessageBox������OpenProcess����Ҫ�Ȼָ�HOOK,�����ǵ��üٺ������Ӷ���ɶ�ջ������������
	::MessageBox(NULL, "OpenProcess�ѱ�HOOK", "�޷�ʹ��", MB_OK);
	hookapi();
    return NULL;
}  

void getapi() {		//��ȡԭAPI��ַ
	  HMODULE hmodule=::LoadLibrary("kernel32.dll");
	  openprocess=(OldOpenProcess)::GetProcAddress(hmodule, "OpenProcess");  
	  pfOldOpenProcess=(FARPROC)openprocess; 
}

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
	hprocess=OpenProcess(PROCESS_ALL_ACCESS,0, ::GetCurrentProcessId());
	WriteProcessMemory(hprocess, pfOldOpenProcess, NewCode, 5, 0);  //�޸�API�������ǰ5���ֽ�Ϊjmp xxxxxx  
}

void unhookapi() {
	hprocess=hprocess2;		//�ָ���ǰ���̾����������OpenProcess��
	WriteProcessMemory(hprocess, pfOldOpenProcess, OldCode, 5, 0);  //�޸�API�������ǰ5���ֽ�Ϊjmp xxxxxx    
}

void test() {
    HWND h = ::FindWindow(NULL, "�½� �ı��ĵ�.txt - ���±�");  //  Ѱ�Ҳ��򿪽���
    DWORD processid = 0;
    GetWindowThreadProcessId(h, &processid);
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	cout << "���̾��" << hprocess << endl;
}

int main() {
	getapi();
	savecode();

	test();		//hookǰ��OpenProcess�򿪼��±�

	hookapi();
	hprocess2=hprocess;		//���浱ǰ���̾��
	test();		//hook����OpenProcess�򿪼��±�

	unhookapi();
	test();		//�ָ�hook����OpenProcess�򿪼��±�

	return 0;
}