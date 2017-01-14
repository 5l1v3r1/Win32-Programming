#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <conio.h>

typedef  DWORD (WINAPI *SUSPENDPROCESS)(HANDLE);
typedef  DWORD (WINAPI *RESUMEPROCESS)(HANDLE);

SUSPENDPROCESS SuspendProcess;
RESUMEPROCESS ResumeProcess;


int ProcProcess(LPSTR lpFillName)
{
    PROCESSENTRY32    stProcess;
    stProcess.dwSize = sizeof (PROCESSENTRY32);

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (NULL == hSnapShot) {
        return 0; //�������̿���ʧ��
    }

    BOOL bLoop = Process32First(hSnapShot, &stProcess);
    while (bLoop)
    {
        CharLower(stProcess.szExeFile);
        if (0 == lstrcmp(lpFillName, stProcess.szExeFile))
        {
            //MessageBox(NULL, (LPCTSTR)TEXT("�н���"), (LPCTSTR)TEXT("��Ϣ"), MB_OK | MB_ICONINFORMATION);
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, stProcess.th32ProcessID);
            if (NULL == hProcess) {
                //�򿪽���ʧ��
                return 0;
            }
            SuspendProcess(hProcess);
            int ret = MessageBox(NULL, (LPCTSTR)TEXT("Ŀ������Ƿ�ر�?"), (LPCTSTR)TEXT("ѯ��"), MB_YESNO | MB_ICONQUESTION);
            if (IDYES == ret) {
                //�ر�
                TerminateProcess(hProcess, 0);
            } else {
                //���ر�, ȡ�����̹���״̬
                lpFillName[0] = 0;
                ResumeProcess(hProcess);
            }

            CloseHandle(hProcess);

        }
        bLoop = Process32Next(hSnapShot, &stProcess);
    }

    CloseHandle(hSnapShot); //�رս��̿���
    return 1;
}

HINSTANCE InitDll()
{
    HINSTANCE    hDllInstance = LoadLibrary((LPCSTR)TEXT("NTDLL.DLL"));
    if (NULL == hDllInstance) {
        MessageBox(NULL,
            (LPCSTR)TEXT("NTDll.dll�ļ���ʧ��װ��ʧ��, �������޷�ʵ��"),
            (LPCSTR)TEXT("ʧ��"), MB_OK | MB_ICONERROR);
        return NULL;
    }
   
    SuspendProcess = (SUSPENDPROCESS)GetProcAddress(hDllInstance, (LPCSTR)TEXT

("ZwSuspendProcess"));
    if (NULL == SuspendProcess) {
        MessageBox(NULL,
            (LPCSTR)TEXT("ntdll.dll�򲻵�����ZwSuspendProcess"),
            (LPCSTR)TEXT("ʧ��"), MB_OK | MB_ICONERROR);
        CloseHandle(hDllInstance);
        return NULL;
    }
   
    ResumeProcess = (RESUMEPROCESS)GetProcAddress(hDllInstance, (LPCSTR)TEXT

("ZwResumeProcess"));
    if (NULL == ResumeProcess) {
        MessageBox(NULL,
            (LPCSTR)TEXT("ntdll.dll�򲻵�����ResumeProcess"),
            (LPCSTR)TEXT("ʧ��"), MB_OK | MB_ICONERROR);
        CloseHandle(hDllInstance);
        return NULL;
    }
    return hDllInstance;
}

void Exit(HINSTANCE hDllInstance)
{
    FreeLibrary(hDllInstance);
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    while (TRUE)
    {
        ProcProcess((LPSTR)lpParameter);
        Sleep(100);
    }
    return 0;
}


int main(int argc, char* argv[])
{
    TCHAR    lpFileName[MAX_PATH];
    printf("�������������(��ת��Сд):");
    scanf("%s", lpFileName);

    CharLower(lpFileName);    //ת��Сд
   
    HINSTANCE hDllInstance = InitDll();

    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)lpFileName, NULL, NULL);
    CloseHandle(hThread);
    Sleep(20000);
    Exit(hDllInstance);
    return 0;
}