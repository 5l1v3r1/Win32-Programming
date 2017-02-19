
// Spy++Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Spy++.h"
#include "Spy++Dlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

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


// CSpyDlg �Ի���




CSpyDlg::CSpyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpyDlg::IDD, pParent)
	, m_cs_process(_T(""))
	, m_cs_hwnd(_T(""))
	, m_cs_title(_T(""))
	, m_cs_class(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CURSOR, m_pic);
	DDX_Text(pDX, IDC_EDIT_PROCESS, m_cs_process);
	DDX_Text(pDX, IDC_EDIT_HWND, m_cs_hwnd);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_cs_title);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_cs_class);
	DDX_Control(pDX, IDC_CHECK_HIDE, m_btn_hide);
}

BEGIN_MESSAGE_MAP(CSpyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_HIDE, &CSpyDlg::OnBnClickedCheckHide)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSpyDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CSpyDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CSpyDlg ��Ϣ�������
HCURSOR hcready, hcempty;
BOOL CSpyDlg::OnInitDialog()
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
	hcready = (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR_CHOOSE),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
	hcempty = (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR_WAIT),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
	m_pic.SetCursor(hcready);
	m_bhide = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpyDlg::OnPaint()
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
HCURSOR CSpyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSpyDlg::OnBnClickedCheckHide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bhide = !m_bhide;
}


BOOL CSpyDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pos;   
	GetCursorPos(&pos);  //��ȡ��ǰ���λ��   

	CRect rc;
	CWnd *bkg=GetDlgItem(IDC_STATIC_CURSOR);
	bkg->GetWindowRect(&rc);
	if (rc.PtInRect(pos)) 
	{   
		SetCursor(LoadCursor(NULL, IDC_HAND));
		return true;
	}   
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}



void CSpyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pos;   
	GetCursorPos(&pos);  //��ȡ��ǰ���λ��   
	CRect rc;
	CWnd *bkg=GetDlgItem(IDC_STATIC_CURSOR);
	bkg->GetWindowRect(&rc);

	if (m_bhide) {
		ShowWindow(SW_HIDE);
	}

	if (rc.PtInRect(pos))   //���λ����ͼ����
	{   
		HCURSOR hp; 
		hp= (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR_POINT),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
		::SetCursor(hp);
		::SetCapture(m_hWnd);	//���ֽ���״̬
		m_pic.SetCursor(hcempty);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSpyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hp;
	hp= (HCURSOR)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE) ;
	::SetCursor(hp);
	::ReleaseCapture();
	m_pic.SetCursor(hcready);
	EraseFrame(holdwnd);

	ShowWindow(SW_SHOW);

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CSpyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pos;   
	GetCursorPos(&pos);  //��ȡ��ǰ���λ��   
	CRect rc;
	CWnd *bkg=AfxGetApp()->GetMainWnd();
	bkg->GetWindowRect(&rc);
	if (rc.PtInRect(pos))   //���λ����ͼ����
		return;

	::ClientToScreen(m_hWnd, &point);	//ȡ�������
	HWND hwnd = ::WindowFromPoint(point);	//������Ӧ�Ĵ���
	if ( hwnd == holdwnd)	//��һֱ����ͬ���ں��Լ�
		return;

	EraseFrame(holdwnd);
	DrawFrame(hwnd);
	GetInfo(hwnd);
	holdwnd = hwnd;
	CDialogEx::OnMouseMove(nFlags, point);
}


void CSpyDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CSpyDlg::OnBnClickedButtonHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::MessageBox(NULL, L"������϶���־�ƶ���Ҫ��ѯ�Ĵ��ڼ�����ʾ��Ϣ", L"������Ϣ", MB_ICONINFORMATION);
}


void CSpyDlg::DrawFrame(HWND hwnd)
{
	HDC hdc = ::GetWindowDC(hwnd);
	RECT rect;
	::GetWindowRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HPEN hpen = ::CreatePen(PS_SOLID, 5, RGB(255,0,0));
	HPEN holdpen = (HPEN)::SelectObject(hdc, hpen);

	::MoveToEx(hdc, 0, 0, NULL);
	::LineTo(hdc, width, 0);
	::LineTo(hdc, width, height);
	::LineTo(hdc, 0, height);
	::LineTo(hdc, 0, 0);

	::SelectObject(hdc, holdpen);
	::DeleteObject(hpen);
	::ReleaseDC(hwnd, hdc);
}


void CSpyDlg::EraseFrame(HWND hwnd)
{
	::RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	HWND hparent = ::GetParent(hwnd);
	if (::IsWindow(hparent)) {
		::RedrawWindow(hparent, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}
}


void CSpyDlg::GetInfo(HWND hwnd)
{
	WCHAR wbuff[255];
	::GetWindowText(hwnd, wbuff, sizeof(wbuff));	//����
	m_cs_title = wbuff;

	::GetClassName(hwnd, wbuff, sizeof(wbuff));		//����
	m_cs_class = wbuff;

	wsprintf(wbuff, L"%x", hwnd);			//���ھ��
	m_cs_hwnd = wbuff;

	DWORD pid;		//��������
	::GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return;
	bool bFound=false;
	PROCESSENTRY32 pe32 = {sizeof(pe32)};
	if (::Process32First(hProcessSnap, &pe32)) {
		do {
			if (pe32.th32ProcessID == pid) {
				bFound = true;
				break;
			}
		} while(::Process32Next(hProcessSnap, &pe32));
	}
	if (bFound) {
			wsprintf(wbuff, pe32.szExeFile);
	} else {
			wsprintf(wbuff, L"�Ҳ�������");
	}
	m_cs_process = wbuff;
	UpdateData(false);
}
