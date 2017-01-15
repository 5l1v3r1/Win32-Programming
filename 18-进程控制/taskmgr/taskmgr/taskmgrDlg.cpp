
// taskmgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "taskmgr.h"
#include "taskmgrDlg.h"
#include "afxdialogex.h"
#include <tlhelp32.h>

///////////////////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>

typedef  DWORD (WINAPI *SUSPENDPROCESS)(HANDLE);
typedef  DWORD (WINAPI *RESUMEPROCESS)(HANDLE);

SUSPENDPROCESS SuspendProcess;
RESUMEPROCESS ResumeProcess;

HINSTANCE InitDll() {
	HINSTANCE hDllInstance = LoadLibrary(_T("NTDLL.DLL"));	//����nt.dll
	if (hDllInstance != NULL) {
		SuspendProcess = (SUSPENDPROCESS)GetProcAddress(hDllInstance, "ZwSuspendProcess");	//����SuspendProcess
		if (NULL == SuspendProcess) {
			MessageBox(NULL, _T("ntdll.dll�򲻵�����ZwSuspendProcess"), _T("ʧ��"), MB_ICONERROR);
			CloseHandle(hDllInstance);
			return NULL;
		}
		ResumeProcess = (RESUMEPROCESS)GetProcAddress(hDllInstance, "ZwResumeProcess");	//����ResumeProcess
		if (NULL == ResumeProcess) {
			MessageBox(NULL, _T("ntdll.dll�򲻵�����ResumeProcess"), _T("ʧ��"), MB_ICONERROR);
			CloseHandle(hDllInstance);
			return NULL;
		}
	} else  {
		MessageBox(NULL, _T("NTDll.dll�ļ���ʧ��װ��ʧ��, �������޷�ʵ��"), _T("ʧ��"), MB_ICONERROR);
		return NULL;
	}
	return hDllInstance;
}








////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtaskmgrDlg �Ի���




CtaskmgrDlg::CtaskmgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtaskmgrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtaskmgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_process);
}

BEGIN_MESSAGE_MAP(CtaskmgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FRESH, &CtaskmgrDlg::OnBnClickedButtonFresh)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CtaskmgrDlg::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON_KILL, &CtaskmgrDlg::OnBnClickedButtonKill)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CtaskmgrDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CtaskmgrDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CtaskmgrDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CtaskmgrDlg ��Ϣ�������
CListCtrl *listctrl;
BOOL CtaskmgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	list_process.InsertColumn(0, _T("��������"),  0, 190);
	list_process.InsertColumn(1, _T("����ID��"),  0, 100);
	list_process.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listctrl = &list_process;
	 InitDll();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtaskmgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtaskmgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtaskmgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtaskmgrDlg::OnBnClickedButtonFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list_process.DeleteAllItems();

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hpsnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	//��ǰ���н��̿���
	if (hpsnap == INVALID_HANDLE_VALUE)
		::MessageBox(NULL, _T("CreateToolhelp32Snapshot����"),  _T("ʧ��"), MB_ICONERROR);

	int i = 0;
	BOOL bnext = ::Process32First(hpsnap, &pe32);	//������ǰ���̿���
	while (bnext) {
		list_process.InsertItem(i, pe32.szExeFile);
		CString buff;
		buff.Format(_T("%d"), pe32.th32ProcessID);
		list_process.SetItemText(i, 1, buff);
		bnext = ::Process32Next(hpsnap, &pe32);
	}

	::CloseHandle(hpsnap);
}


int nameup = -1;
int idup = -1;

 int   CALLBACK   cmp(LPARAM   lParam1,   LPARAM   lParam2,   LPARAM   lParamSort) {
	 if (lParamSort == 0) {		//�Խ�����������
		 if (nameup == -1 || nameup == 1) {
			CString strItem1   =   listctrl->GetItemText(lParam1,   0);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   0); 
			return wcscmp(strItem1, strItem2);
		 } else {
			CString strItem1   =   listctrl->GetItemText(lParam1,   0);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   0); 
			return wcscmp(strItem2, strItem1);
		 }
	 } else {		//�Խ���ID����
		 if (idup == -1 || idup == 1) {
			CString strItem1   =   listctrl->GetItemText(lParam1,   1);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   1); 
			return _ttoi(strItem1) > _ttoi(strItem2);
		 } else {
			CString strItem1   =   listctrl->GetItemText(lParam1,   1);  
			CString strItem2   =   listctrl->GetItemText(lParam2,   1); 
			return _ttoi(strItem1) < _ttoi(strItem2);
		 }
	 }
	 return 0;
 }

void CtaskmgrDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int col = pNMLV->iItem;					//������
	int row = pNMLV->iSubItem;				//������

	if (col == -1) {
		CHeaderCtrl* pListHeader = list_process.GetHeaderCtrl();
		HDITEM hditem;
		enum   { sizeOfBuffer = 256 };
		TCHAR  lpBuffer[sizeOfBuffer];
		hditem.mask = HDI_TEXT;
		hditem.pszText = lpBuffer;
		hditem.cchTextMax = sizeOfBuffer;
		pListHeader->GetItem(0, &hditem);
		if (row == 0) {				//��������������
			for(int i=0;i<list_process.GetItemCount();i++)  
				list_process.SetItemData(i,i);
			list_process.SortItems(cmp, 0);

			if (nameup == -1 || nameup == 1) {
				hditem.pszText = _T("�������ơ�");
				pListHeader->SetItem(0, &hditem);
				nameup = 0;
			} else {
				hditem.pszText = _T("�������ƨ�");
				pListHeader->SetItem(0, &hditem);
				nameup = 1;
			}
			hditem.pszText = _T("����id��");
			pListHeader->SetItem(1, &hditem);
		} else if (row == 1) {	//������ID������
			for(int i=0;i<list_process.GetItemCount();i++)  
				list_process.SetItemData(i,i);
			list_process.SortItems(cmp, 1);

			pListHeader->GetItem(1, &hditem);
			if (idup == -1 || idup == 1) {
				hditem.pszText = _T("����id�š�");
				pListHeader->SetItem(1, &hditem);
				idup = 0;
			 } else {
				hditem.pszText = _T("����id�Ũ�");
				pListHeader->SetItem(1, &hditem);
				idup = 1;
			 }
			hditem.pszText = _T("��������");
			pListHeader->SetItem(0, &hditem);
		}
	}
	*pResult = 0;
}

void CtaskmgrDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WCHAR buff[250];
	TRACE("%d ", list_process.GetSelectionMark());
	list_process.GetItemText(list_process.GetSelectionMark(), 0, buff, sizeof(buff));
	TRACE(buff);
	TRACE(" ");
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	TRACE(buff);
	TRACE("\n");
	*pResult = 0;
}


void CtaskmgrDlg::OnBnClickedButtonKill()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int selectitem = list_process.GetSelectionMark();
	if (selectitem == -1) {
		::MessageBox(NULL, _T("δѡ��Ŀ��"), _T("����"), MB_ICONERROR);
		return;
	}
	WCHAR buff[250];
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	DWORD processid = _wtoi(buff);
	HANDLE hprocess = NULL;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (hprocess != NULL) {
		//��ֹ����
		BOOL ret = ::TerminateProcess(hprocess, 0);
		if (ret)
			::MessageBox(NULL, _T("�ѽ���Ŀ��"), _T("�ɹ�"), MB_ICONINFORMATION);
		else
			::MessageBox(NULL, _T("�޷�����Ŀ��"), _T("ʧ��"), MB_ICONERROR);
	} else
		::MessageBox(NULL, _T("�޷���Ŀ��"), _T("����"), MB_ICONERROR);
}

void CtaskmgrDlg::OnBnClickedButtonPause()
{
	 //TODO: �ڴ���ӿؼ�֪ͨ����������
	int selectitem = list_process.GetSelectionMark();
	if (selectitem == -1) {
		::MessageBox(NULL, _T("δѡ��Ŀ��"), _T("����"), MB_ICONERROR);
		return;
	}
	WCHAR buff[250];
	list_process.GetItemText(list_process.GetSelectionMark(), 1, buff, sizeof(buff));
	DWORD processid = _wtoi(buff);
	HANDLE hprocess = NULL;
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (hprocess != NULL) {	//�����ָ�����,�������֪��Ϊ����������Ŷ������ϻָ��Ļ��ͻָ�����
			SuspendProcess(hprocess);
			::MessageBox(NULL, _T("�Ѷ���Ŀ��"), _T("�ɹ�"), MB_ICONINFORMATION);

			int ret = ::MessageBox(NULL,_T("��δ���ѡ��Ŀ�����?YES�ر�NO�ָ�"), _T("ȷ��"), MB_YESNO | MB_ICONQUESTION);
			if (ret ==IDYES ) {				 //�ر�
				TerminateProcess(hprocess, 0);
				::MessageBox(NULL, _T("�ѹر�Ŀ��"), _T("�ɹ�"), MB_ICONINFORMATION);
			} else {									 //���ر�, �ָ�����״̬
				ResumeProcess(hprocess);
				::MessageBox(NULL, _T("�ѻָ�Ŀ��"), _T("�ɹ�"), MB_ICONINFORMATION);
			}
	} else
		::MessageBox(NULL, _T("�޷���Ŀ��"), _T("����"), MB_ICONERROR);
	CloseHandle(hprocess);
}


void CtaskmgrDlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}
