
// TestSQLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSQL.h"
#include "TestSQLDlg.h"
#include "afxdialogex.h"
#include "mysql.h"

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


// CTestSQLDlg �Ի���




CTestSQLDlg::CTestSQLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestSQLDlg::IDD, pParent)
	, cs_sql(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SQL, cs_sql);
}

BEGIN_MESSAGE_MAP(CTestSQLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTestSQLDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_EXE, &CTestSQLDlg::OnBnClickedButtonExe)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CTestSQLDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CTestSQLDlg ��Ϣ�������

BOOL CTestSQLDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestSQLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestSQLDlg::OnPaint()
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
HCURSOR CTestSQLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestSQLDlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CTestSQLDlg::OnBnClickedButtonExe()
{
	//��ʼ�����ݿ�����
	MYSQL mysql;
	mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,"localhost","root","root","db_mfc",3306,NULL,0))  {  
		MessageBox(L"�޷����ӵ����ݿ�", L"����", MB_ICONERROR);
		return;
    }

	//ִ�����ݿ������ ע��mysql_query()�ķ���ֵ�ݺܶ����Σ� �����ж�ʹҪע��
	UpdateData(true);
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,cs_sql,-1,NULL,NULL,0,NULL);
	char *sql = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP,NULL,cs_sql,-1,sql,dwNum,0,NULL);
	mysql_query(&mysql, "set names 'utf8'");
	if ( mysql_query(&mysql, sql )==0 ) {
		MessageBox(L"ִ�����ݿ�����ɹ�", L"�ɹ�", MB_ICONINFORMATION);
	} else {
		MessageBox(L"ִ�����ݿ����ʧ��", L"ʧ��", MB_ICONERROR);
	}

	//�ر����ݿ�����
	mysql_close(&mysql);
	UpdateData(false);
}


void CTestSQLDlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cs_sql = L"";
	UpdateData(false);
}
