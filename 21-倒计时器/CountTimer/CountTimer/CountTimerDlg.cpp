
// CountTimerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CountTimer.h"
#include "CountTimerDlg.h"
#include "afxdialogex.h"
#define WM_USER_UPDATEDTA WM_USER+1

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


// CCountTimerDlg �Ի���




CCountTimerDlg::CCountTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCountTimerDlg::IDD, pParent)
	, cs_time(_T(""))
	, cs_counttime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCountTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, start);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, pause);
	DDX_Control(pDX, IDC_BUTTON_STOP, stop);
	DDX_Text(pDX, IDC_EDIT2, cs_time);
	DDX_Text(pDX, IDC_EDIT1, cs_counttime);
}

BEGIN_MESSAGE_MAP(CCountTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CCountTimerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CCountTimerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CCountTimerDlg::OnBnClickedButtonPause)
END_MESSAGE_MAP()


// CCountTimerDlg ��Ϣ�������
CString *pcs_counttime;
CButton *pstart;
CButton *ppause;
CButton *pstop;
BOOL CCountTimerDlg::OnInitDialog()
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
	start.EnableWindow(true);
	stop.EnableWindow(false);
	pause.EnableWindow(false);
	pcs_counttime = &cs_counttime;
	cs_counttime.Format(L"0.0");
	pstart = &start;
	ppause = &pause;
	pstop = &stop;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCountTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCountTimerDlg::OnPaint()
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
HCURSOR CCountTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

float f_time = 0;
float f_oldtime = 0;
bool bpause = false;
HANDLE hcountdown = NULL;
DWORD WINAPI countdown(LPVOID lpParam) {
	while (f_time>=0) {
		HWND hwnd = AfxGetApp()->m_pMainWnd->m_hWnd;
		HDC hdc = ::GetDC(hwnd);
		float percent = f_time/f_oldtime; 
		::Rectangle(hdc, 65,20,65+(173-65)*percent,45);
		ReleaseDC(hwnd, hdc);
		f_time -= 0.005;
		Sleep(5);
		AfxGetApp()->m_pMainWnd->SendMessage(WM_USER_UPDATEDTA, 0, 0);
	}
	f_time = 0;
	bpause = false;
	pstart->EnableWindow(true);
	pstop->EnableWindow(false);
	ppause->EnableWindow(false);
	pcs_counttime->Format(L"0.0");
	AfxGetApp()->m_pMainWnd->SendMessage(WM_USER_UPDATEDTA, 0, 0);
	return 0;
}

void CCountTimerDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!bpause) {
		UpdateData(true);
		float count = _tstof(cs_time);
		if (!count) {
			::MessageBox(NULL, L"���ݲ���ȷ���ʽ����", L"����", MB_ICONERROR);
			return;
		} else {
			f_time = count;
			f_oldtime = f_time;
			hcountdown = CreateThread(NULL, 0, countdown, NULL, 0, NULL);
			start.EnableWindow(false);
			stop.EnableWindow(true);
			pause.EnableWindow(true);
		}
	} else {
		start.SetWindowText(L"��ʼ");
		::ResumeThread(hcountdown);
		start.EnableWindow(false);
		stop.EnableWindow(true);
		pause.EnableWindow(true);
	}
}


LRESULT CCountTimerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (message == WM_USER_UPDATEDTA) {
		cs_counttime.Format(L"%.2f", f_time);
		this->UpdateData(false);
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CCountTimerDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwExitCode;
	GetExitCodeThread(hcountdown, &dwExitCode);
	if (dwExitCode==STILL_ACTIVE) {
		::TerminateThread(hcountdown, 0);
		start.EnableWindow(true);
		stop.EnableWindow(false);
		pause.EnableWindow(false);
		cs_counttime.Format(L"0.0");
		bpause = false;
		this->UpdateData(false);
	} else {
		::MessageBox(NULL, L"����ʱ�Ѿ�����", L"����", MB_ICONERROR);
	}
}


void CCountTimerDlg::OnBnClickedButtonPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwExitCode;
	GetExitCodeThread(hcountdown, &dwExitCode);
	if (dwExitCode==STILL_ACTIVE) {
		::SuspendThread(hcountdown);
		start.SetWindowText(L"����");
		start.EnableWindow(true);
		stop.EnableWindow(false);
		pause.EnableWindow(false);
		this->UpdateData(false);
		bpause = true;
	} else {
		::MessageBox(NULL, L"����ʱ�Ѿ�����", L"����", MB_ICONERROR);
	}
}
