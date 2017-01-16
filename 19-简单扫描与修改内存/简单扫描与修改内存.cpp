#include <windows.h>
#include <Tlhelp32.h>
#include <iostream>

#define MAXSIZE 5000

class CMemFinder {
	protected:
		int m_dwlistnum;
		BOOL m_bfirst;
		HANDLE m_hprocess;
		DWORD m_dwlist[MAXSIZE];
		virtual BOOL ComparePage(DWORD dwBaseAddr, DWORD dwValue);
	public:
		CMemFinder(DWORD processid);	//��ʼ��������������
		CMemFinder(WCHAR *processname);
		CMemFinder(char &windowname);
		virtual ~CMemFinder();

		virtual void ShowList();	//��������
		virtual BOOL FindFirst(DWORD dwVaule);
		virtual BOOL FindNext(DWORD dwVaule);
		virtual BOOL modify(DWORD dwAddr, DWORD dwValue);
};

CMemFinder::CMemFinder(DWORD processid) {		//���ݽ���id��Ѱ�Ҳ��򿪽���
	m_dwlistnum = 0;
	m_hprocess = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	if (NULL ==m_hprocess) {
		printf( "�򿪽���ʧ��\n");
		return;
	}
	printf( "�򿪽��̳ɹ�\n");
}

CMemFinder::CMemFinder(WCHAR *processname) {		//���ݽ�����Ѱ�Ҳ��򿪽���
	m_dwlistnum = 0;
	PROCESSENTRY32	stProcess;
	stProcess.dwSize = sizeof (PROCESSENTRY32);
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot ==NULL ) {
		return;
	}
	bool isfound = false;
	BOOL bLoop = Process32First(hSnapShot, &stProcess);
	while (bLoop && !isfound) {
		CharLower((LPWSTR)processname);
		CharLower(stProcess.szExeFile);
		if (0 == lstrcmp((LPCWSTR)processname, stProcess.szExeFile)) {
			m_hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, stProcess.th32ProcessID);
			if (NULL ==m_hprocess) {
				printf( "�򿪽���ʧ��\n");
				return;
			}
			printf( "�򿪽��̳ɹ�\n");
			isfound = true;
		}
		bLoop = Process32Next(hSnapShot, &stProcess);
	}
	if (!isfound)
		printf( "�Ҳ���Ŀ��\n");
}

CMemFinder::CMemFinder(char &windowname) {		//���ݴ�����Ѱ�Ҳ��򿪽���
	m_dwlistnum = 0;
	WCHAR wbuff[255];
	int dwNum=sizeof(windowname);
	MultiByteToWideChar (CP_ACP, 0, (LPCSTR)windowname, -1, wbuff, dwNum);
    HWND h = ::FindWindow(NULL, wbuff);	
    DWORD processid;
    GetWindowThreadProcessId(h, &processid);
    m_hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (NULL ==m_hprocess) {
		printf( "�򿪽���ʧ��\n");
		return;
	}
	printf( "�򿪽��̳ɹ�\n");
}

CMemFinder::~CMemFinder() {

}

BOOL CMemFinder::ComparePage(DWORD dwBaseAddr, DWORD dwValue) {	//��ҳ��ȡ�ڴ�
	BYTE arBytes[4096];
	if (!::ReadProcessMemory(m_hprocess, (LPCVOID)dwBaseAddr, arBytes, 4096, NULL))
		return false;		//���ɶ�������ʧ��
	DWORD *pdw;
	for (int i = 0; i < 4 * 1024 - 3; i++) {
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue) {
			if (m_dwlistnum >= MAXSIZE)
				return false;
			m_dwlist[m_dwlistnum++] = dwBaseAddr + i;
		}
	}
	return true;
}

BOOL CMemFinder::FindFirst(DWORD dwValue) {
	const DWORD dwGB = 1<<30;
	const DWORD dwOnePage = 4*1024;
	if (m_hprocess == NULL)
		return false;
	//�鿴����ϵͳ���ͣ�������ʼ��ַ
	DWORD dwBase;
	OSVERSIONINFO vi = {sizeof(vi)};
	::GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
		dwBase = 4*1024*1024;	//98ϵ��4MB
	else
		dwBase = 640*1024;	//windowsNTϵ��64KB
	for(; dwBase < 2*dwGB; dwBase += dwOnePage)
		ComparePage(dwBase, dwValue);
	return true;
}

BOOL CMemFinder::FindNext(DWORD dwValue) {	//�ٴ�ɨ��
	int orgnum = m_dwlistnum;
	m_dwlistnum = 0;
	BOOL flag = false;	//����ʧ��
	DWORD dwReadValue;
	for (int i = 0; i < orgnum; i++)
		if (::ReadProcessMemory(m_hprocess, (LPVOID)m_dwlist[i], &dwReadValue, sizeof(DWORD),NULL))
			if (dwReadValue == dwValue) {
				m_dwlist[m_dwlistnum++] = m_dwlist[i];
				flag = true;
			}
	return flag;
}

BOOL CMemFinder::modify(DWORD dwAddr, DWORD dwValue) {
	return ::WriteProcessMemory(m_hprocess, (LPVOID)dwAddr, &dwValue, sizeof(DWORD), NULL);
}

void CMemFinder::ShowList() {
	if (!m_dwlistnum)
		printf("������\n");
	for (int i = 0; i < m_dwlistnum; i++)
		printf("%08x\n", m_dwlist[i]);
}

int main() {
	WCHAR ws[]= TEXT("test.exe");
	CMemFinder ce(ws);	//�ӽ���������
	printf("��һ�β���=========\n");
	ce.FindFirst(100);
	ce.ShowList();
	printf("�ڶ��β���=========\n");
	ce.FindNext(101);
	ce.ShowList();
	printf("�޸�=========\n");
	ce.modify(1638212, 200);
	return 0;
}