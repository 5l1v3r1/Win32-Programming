
// FileMonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileMonitor.h"
#include "FileMonitorDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hmonitor = NULL;
WCHAR  dirname[MAX_PATH+50]; 
CListBox *mylistbox;
void setlistbox(int size);
bool start = false;
WCHAR timebuff[MAX_PATH+50];

void gettime(bool style = true) {
	CTime time = CTime::GetCurrentTime();///����CTime����
	int m_nYear = time.GetYear();///��
	int m_nMonth = time.GetMonth();///��
	int m_nDay = time.GetDay();///��
	int m_nHour = time.GetHour();///Сʱ
	int m_nMinute = time.GetMinute();///����
	int m_nSecond = time.GetSecond();///��
	CString m_strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	if (!style)
		m_strTime = time.Format(_T("%Y-%m-%d %H;%M;%S"));
	WCHAR *buff = m_strTime.GetBuffer(MAX_PATH+50);
	std::wcscpy(timebuff, buff);
	m_strTime.ReleaseBuffer();
}

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


// CFileMonitorDlg �Ի���




CFileMonitorDlg::CFileMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTBOX, listbox);
	DDX_Control(pDX, IDC_BUTTON_START, button_start);
}

BEGIN_MESSAGE_MAP(CFileMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEFILE, &CFileMonitorDlg::OnBnClickedButtonChoosefile)
	ON_BN_CLICKED(IDC_BUTTON_START, &CFileMonitorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CFileMonitorDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CFileMonitorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CFileMonitorDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


DWORD WINAPI monitor(LPVOID) {
	bool once = true;
	BOOL bRet = FALSE;
	BYTE Buffer[1024] = {0};

	FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer;
	DWORD dwByteReturn = 0;
	HANDLE hFile = ::CreateFile(dirname, FILE_LIST_DIRECTORY, 
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if(INVALID_HANDLE_VALUE == hFile) {
		::MessageBox(NULL, _T("���ļ�Ŀ¼����"), _T("����"), MB_ICONERROR);
		return 1;
	}
	while(TRUE) {
		::ZeroMemory(Buffer, sizeof(Buffer));
		bRet = ::ReadDirectoryChangesW(hFile, 
			&Buffer,
			sizeof(Buffer),
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |			// �޸��ļ���
			FILE_NOTIFY_CHANGE_ATTRIBUTES |			// �޸��ļ�����
			FILE_NOTIFY_CHANGE_LAST_WRITE,			// ���һ��д��
			&dwByteReturn, NULL, NULL);				
		if(TRUE == bRet) {
			char szFileName[MAX_PATH+50] = {0};

			// ���ַ�ת��Ϊ���ֽ�
			::WideCharToMultiByte(CP_ACP,
				0,
				pBuffer->FileName,
				(pBuffer->FileNameLength / 2),
				szFileName,
				MAX_PATH+50,
				NULL,
				NULL);
			switch(pBuffer->Action) {
				case FILE_ACTION_ADDED:
					{
						once = true;
						WCHAR buff[MAX_PATH+50];
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("���: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				case FILE_ACTION_REMOVED:
					{
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("ɾ��: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				case FILE_ACTION_MODIFIED:
					{
						if (!once) {
							once = !once;
							break;
						}
						once = !once;
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("�޸�: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				case FILE_ACTION_RENAMED_OLD_NAME:
					{
						once = false;	//��ֹ�ظ���¼
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("������: "));
						std::wcscat(buff, pBuffer->FileName);
						if(0 != pBuffer->NextEntryOffset) {
							FILE_NOTIFY_INFORMATION *tmpBuffer = (FILE_NOTIFY_INFORMATION *)
								((DWORD)pBuffer + pBuffer->NextEntryOffset);
							switch(tmpBuffer->Action)
								{
									case FILE_ACTION_RENAMED_NEW_NAME:
										{
												::ZeroMemory(szFileName, MAX_PATH+50);
												::WideCharToMultiByte(CP_ACP,
													0,
													tmpBuffer->FileName,
													(tmpBuffer->FileNameLength / 2),
													szFileName,
													MAX_PATH+50,
													NULL,
													NULL);
												std::wcscat(buff, _T(" -> "));
												std::wcscat(buff, tmpBuffer->FileName);
												setlistbox(wcslen(buff));
												mylistbox->AddString(buff);
												break;
										}
								}
						}
						break;
					}
				case FILE_ACTION_RENAMED_NEW_NAME:
					{
						WCHAR buff[MAX_PATH+50]; 
						gettime();
						std::wcscpy(buff, timebuff);
						std::wcscat(buff, _T("     \t"));
						std::wcscat(buff, _T("������: "));
						std::wcscat(buff, pBuffer->FileName);
						setlistbox(wcslen(buff));
						mylistbox->AddString(buff);
						break;
					}
				}
		}
	}


	return 0;
}

// CFileMonitorDlg ��Ϣ�������
BOOL CFileMonitorDlg::OnInitDialog()
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
	mylistbox = &listbox;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFileMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileMonitorDlg::OnPaint()
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
HCURSOR CFileMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int max = 0;
void setlistbox(int oldsize) {
	int size = oldsize * 8.5;
	if (size > max) {
		max = size;
		mylistbox->SetHorizontalExtent(max);
	}
}


void CFileMonitorDlg::OnBnClickedButtonChoosefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool pause = false;
	if (hmonitor != NULL) {
		OnBnClickedButtonStart();
		pause = true;
	}

	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = dirname; 
	bi.lpszTitle = _T("\n��ѡ�����Ŀ¼:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 
	CString sPath;

	if (pidl) { 
		SHGetPathFromIDList(pidl, dirname); 
		sPath = dirname; 
	} else {
		if (dirname[0] == '\0')
			::MessageBox(NULL, _T("δѡ��Ŀ¼"), _T("����"), MB_ICONERROR);
		//memset(dirname, 0, MAX_PATH+50);
	}
	if (dirname[0] != '\0') {
		WCHAR buff[MAX_PATH+50]; 
		std::wcscpy(buff, _T("��ѡ��Ŀ¼: "));
		std::wcscat(buff, dirname);
		setlistbox(wcslen(buff));
		listbox.AddString(buff);
	}

	if (pause) {
		OnBnClickedButtonStart();
	}
}

void CFileMonitorDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (dirname[0] == '\0') {
		::MessageBox(NULL, _T("ѡ��Ŀ¼����"), _T("����"), MB_ICONERROR);
		return;
	}
	if (!start) {
		button_start.SetWindowTextW(_T("�رռ���"));
		hmonitor = ::CreateThread(NULL, 0, monitor, NULL, 0, NULL);
		listbox.EnableWindow(true);
	} else {
		button_start.SetWindowTextW(_T("��ʼ����"));
		::TerminateThread(hmonitor, 0);
		listbox.EnableWindow(false);
	}
	start = !start;
}


WCHAR  exportdir[MAX_PATH+50]; 
WCHAR filetxt[5000000];
char filetxt2[5000000];
std::ofstream of;

void createfile() {

	WCHAR name[MAX_PATH+50];
	std::wcscpy(name, exportdir);
	std::wcscat(name, _T("\\"));
	gettime(false);
	std::wcscat(name, timebuff);
	std::wcscat(name, _T("Ŀ¼�޸ļ�¼.txt"));

	char openname[MAX_PATH+50]; 
	WideCharToMultiByte(CP_OEMCP, NULL, name, -1, openname, sizeof(name), NULL, false);
	of.open(openname,  std::ofstream::out | std::ios::app);
	if (!of) {
		::MessageBox(NULL, _T("��������"), _T("����"), MB_ICONERROR);
		return;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, filetxt, -1, filetxt2, sizeof(filetxt), NULL, false);
	of << filetxt2;
}

void closefile() {
	of.close();
}

void CFileMonitorDlg::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = exportdir; 
	bi.lpszTitle = _T("\n��ѡ�񵼳��ļ�Ŀ¼:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 
	CString sPath;

	if (pidl) { 
		SHGetPathFromIDList(pidl, exportdir); 
		sPath = exportdir; 

		::memset(filetxt, 0 , sizeof(filetxt));
		::memset(filetxt2, 0 , sizeof(filetxt));
		WCHAR mybuff[MAX_PATH+50];
		::memset(mybuff, 0 , sizeof(mybuff));
		for (int i = 0; i < listbox.GetCount(); i++) {
			listbox.GetText(i, mybuff);
			std::wcscat(filetxt, mybuff);
			std::wcscat(filetxt, _T("\r\n"));
		}

		createfile();
		closefile();
		::MessageBox(NULL, exportdir, _T("�ɹ�������"), MB_ICONINFORMATION);
	}
}


void CFileMonitorDlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mylistbox->SetHorizontalExtent(0);
	listbox.ResetContent();
}


void CFileMonitorDlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}
