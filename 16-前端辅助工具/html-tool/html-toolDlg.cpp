
// html-toolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "html-tool.h"
#include "html-toolDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "deque"
#define WM_UPDATEDATA  10000+1

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


// ChtmltoolDlg �Ի���

ChtmltoolDlg::ChtmltoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChtmltoolDlg::IDD, pParent)
	, m_red(_T(""))
	, m_green(_T(""))
	, m_blue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChtmltoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RED, m_red);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_green);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_blue);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_BUTTON_OPACITY, button_opacity);
	DDX_Control(pDX, IDC_BUTTON_FRESH, m_fresh);
	DDX_Control(pDX, IDC_BUTTON_CHOOSEFILE, m_choosefile);
}

BEGIN_MESSAGE_MAP(ChtmltoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(10001, &ChtmltoolDlg::OnUpdatedata)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER, &ChtmltoolDlg::OnTRBNThumbPosChangingSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, &ChtmltoolDlg::OnNMReleasedcaptureSlider)
	ON_BN_CLICKED(IDC_BUTTON_OPACITY, &ChtmltoolDlg::OnBnClickedButtonOpacity)
	ON_BN_CLICKED(IDC_BUTTON_FRESH, &ChtmltoolDlg::OnBnClickedButtonFresh)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEFILE, &ChtmltoolDlg::OnBnClickedButtonChoosefile)
END_MESSAGE_MAP()


int x,y;
int red, green, blue;
COLORREF color;
POINT point;
HWND hwnd;
HWND hdlg;
CString *red_text,*green_text, *blue_text ;

DWORD WINAPI getcolor(LPVOID) {
	while(true) {
		GetCursorPos(&point);
		color = ::GetPixel(::GetDC(hwnd), point.x, point.y);
		red = GetRValue(color);
		green = GetGValue(color);
		blue = GetBValue(color);
		char redbuff[5];
		char greenbuff[5];
		char bluebuff[5];
		std::sprintf(redbuff, "%d", red);
		std::sprintf(greenbuff, "%d", green);
		std::sprintf(bluebuff, "%d", blue);
		*red_text = redbuff;
		*green_text = greenbuff;
		*blue_text = bluebuff;
		::SendMessage(hdlg, WM_UPDATEDATA, FALSE, 0);
		::Sleep(10);
	}
    return 0;
}

std::deque<HWND> hwnds;
DWORD lwa_alpha = LWA_ALPHA;
BYTE value;
CSliderCtrl *slider;
bool opacity = true;
DWORD WINAPI savewindow(LPVOID) {
	while (true) {
		if (!opacity) {
			::Sleep(10);
			continue;
		}
		HWND h = ::GetForegroundWindow();
		WCHAR windowname[250];
		::GetWindowText(h, windowname, 250);
		bool ispushed = false;
		for (auto it = hwnds.begin(); it != hwnds.end();) {
			if (h == *it) {
				it = hwnds.erase(it);
				hwnds.push_back(h);
				ispushed = true;
				if (h != hdlg) {
					GetLayeredWindowAttributes(h, NULL, &value, &lwa_alpha);
					slider->SetPos(value);
				}
				break;
			} else
				it++;
		}
		if (h && !ispushed)
			hwnds.push_back(h);
		::Sleep(10);
	}
	return 0;
}


HWND hchrome = NULL;
void refreshchrome() {	//����chrome��ҳ
	hchrome = NULL;
	hchrome=FindWindow(_T("Chrome_WidgetWin_1"), NULL);
		if (hchrome != NULL) {
		hchrome=GetParent(hchrome);		//Ҫ��������Ӵ��ھ���ҵ������ھ��
		::SetForegroundWindow(hchrome);
		Sleep(5);
		::SendMessage(hchrome, WM_KEYDOWN, VK_F5, 0);
		::SendMessage(hchrome, WM_KEYUP, VK_F5, 0);
	}
}

WCHAR  dirname[MAX_PATH]; 
bool isfresh = true;
DWORD WINAPI checkfile(LPVOID) {
	while (true) {
		if (!isfresh || dirname[0] == 0) {
			::Sleep(10);
			continue;
		}
		HANDLE hcheck = ::FindFirstChangeNotification(dirname, true, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE);
		if (hcheck == INVALID_HANDLE_VALUE) {
			::MessageBox(NULL, _T("�����߳�ʧ��") , _T("ʧ��"), MB_OK);
			return -1;		
		}
		DWORD ret = ::WaitForSingleObject(hcheck, INFINITE);
		if (ret == WAIT_FAILED)
			::MessageBox(NULL, _T("�ȴ�ʧ��") , _T("ʧ��"), MB_OK);
		else if (isfresh) {
			//::MessageBox(NULL, dirname , _T("�ļ��ı�"), MB_OK);
			refreshchrome();
		}
	}
	return 0;
}

BOOL ChtmltoolDlg::OnInitDialog()
{
	hdlg = this->m_hWnd;
	CDialogEx::OnInitDialog();

	// ������ʾ��ɫ�߳�
	red_text = &m_red;
	green_text = &m_green;
	blue_text = &m_blue;
	CreateThread(NULL, 0, getcolor, NULL, 0, NULL);

	// ������ʾ͸�����߳�
	slider = &m_slider;
	m_slider.SetRangeMax(255);
	m_slider.SetTicFreq(10);
	m_slider.SetLineSize(2);
	m_slider.SetPageSize(10);
	m_slider.SetPos(255);
	CreateThread(NULL, 0, savewindow, NULL, 0, NULL);

	// ���������ļ��߳�
	CreateThread(NULL, 0, checkfile, NULL, 0, NULL);


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
	int sysX=GetSystemMetrics(SM_CXSCREEN);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, sysX-482, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ChtmltoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void ChtmltoolDlg::OnPaint()
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
HCURSOR ChtmltoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT ChtmltoolDlg::OnUpdatedata(WPARAM wParam, LPARAM lParam)
{
	UpdateData(false);
	return 0;
}


void ChtmltoolDlg::OnTRBNThumbPosChangingSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

DWORD arg = LWA_ALPHA;
HWND hset;
void ChtmltoolDlg::OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	if (!opacity)
		return;
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	WCHAR windowname[250];

	HWND  hset;
	if (hwnds.size())
		hset = hwnds.back();
	if (hset == hdlg && hwnds.size() >= 2) {
		hset = hwnds[hwnds.size()-2];
		value = (*slider).GetPos();
		SetWindowLong(hset,GWL_EXSTYLE, 0x80000);
		::SetLayeredWindowAttributes(hset, NULL, value, LWA_ALPHA);
	}
}


void ChtmltoolDlg::OnBnClickedButtonOpacity()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (opacity) {
		slider->EnableWindow(false);
		button_opacity.SetWindowTextW(_T("��"));
	} else {
		slider->EnableWindow(true);
		button_opacity.SetWindowTextW(_T("��"));
	}
	opacity = !opacity;
}

void ChtmltoolDlg::OnBnClickedButtonFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!isfresh) {
		m_fresh.SetWindowTextW(_T("��"));
		m_choosefile.EnableWindow(true);
		isfresh = true;
	} else {
		m_fresh.SetWindowTextW(_T("��"));
		m_choosefile.EnableWindow(false);
		isfresh = false;
	}
}

void ChtmltoolDlg::OnBnClickedButtonChoosefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isfresh = false;
	BROWSEINFO bi; 

	LPITEMIDLIST pidl; 
	LPMALLOC pMalloc = NULL;  
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = GetSafeHwnd(); 
	bi.pszDisplayName = dirname; 
	bi.lpszTitle = _T("��ѡ��Ŀ¼,���ָĶ���ˢ��chrome�����:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	pidl = SHBrowseForFolder(&bi); 
	CString sPath;

	if (pidl) { 
		SHGetPathFromIDList(pidl, dirname); // set the directory name. 
		sPath = dirname; // m_sPath��CString׃��������Y�����@����
	}
	//::MessageBox(NULL, dirname , _T("file"), MB_OK);
	isfresh = true;
}
