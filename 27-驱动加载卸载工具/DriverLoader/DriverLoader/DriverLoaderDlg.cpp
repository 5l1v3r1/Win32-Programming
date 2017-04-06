
// DriverLoaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DriverLoader.h"
#include "DriverLoaderDlg.h"
#include "afxdialogex.h"
#include <winsvc.h>

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


// CDriverLoaderDlg �Ի���




CDriverLoaderDlg::CDriverLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDriverLoaderDlg::IDD, pParent)
	, cs_src(_T(""))
	, m_drivername(_T(""))
	, m_driverpath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, cs_src);
}

BEGIN_MESSAGE_MAP(CDriverLoaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SRC, &CDriverLoaderDlg::OnBnClickedButtonSrc)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDriverLoaderDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD, &CDriverLoaderDlg::OnBnClickedButtonUnload)
END_MESSAGE_MAP()


// CDriverLoaderDlg ��Ϣ�������

BOOL CDriverLoaderDlg::OnInitDialog()
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

void CDriverLoaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDriverLoaderDlg::OnPaint()
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
HCURSOR CDriverLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDriverLoaderDlg::OnBnClickedButtonSrc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog sysFile(true, NULL, NULL, 0, L"�����ļ�*.sys|*.sys|�����ļ�*.*|*.*|");
	if (IDOK == sysFile.DoModal()) {
		m_driverpath = sysFile.GetPathName();
		m_drivername = sysFile.GetFileName();
		cs_src = m_drivername;
		UpdateData(false);
	}
}

void CDriverLoaderDlg::OnBnClickedButtonLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!cs_src.IsEmpty()) {
		LoadDriver();
	} else {
		MessageBox(L"δѡ�������ļ�", L"����", MB_ICONERROR);
	}
}

void CDriverLoaderDlg::OnBnClickedButtonUnload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_drivername.IsEmpty() && !m_driverpath.IsEmpty()) {
		UnloadDriver();
	}
}

bool CDriverLoaderDlg::LoadDriver(void)
{
	bool bRet = false;
	SC_HANDLE hServiceMgr=NULL;		//SCM�������ľ��
	SC_HANDLE hServiceDDK=NULL;	//NT��������ķ�����

	hServiceMgr =  ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);	//�򿪷�����ƹ�����
	if (hServiceMgr == NULL) {
		TRACE( "OpenSCManager()ʧ�ܣ�ԭ��=%d\n", GetLastError() );
		goto BExit;
	} else {
		TRACE( "OpenSCManager()�ɹ�\n");
	}

	hServiceDDK = ::CreateService(hServiceMgr, m_drivername,  m_drivername, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, m_driverpath, NULL, NULL, NULL, NULL, NULL);	//������������Ӧ�ķ���
	if (hServiceDDK == NULL) {
		DWORD dwRtn = GetLastError();
		if( dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS )  {  
			TRACE( "��������ԭ�򴴽�����ʧ�ܣ�ԭ��=%d\n", GetLastError() );
			goto BExit;
		}  else  {
			TRACE( "CrateService() ���񴴽�ʧ�ܣ������ڷ����Ѿ���������ԭ��=%d\n", GetLastError() );  
		}

		hServiceDDK = ::OpenService(hServiceMgr, m_drivername, SERVICE_ALL_ACCESS);		// ���������Ѿ����أ�ֻ��Ҫ��  
		if (hServiceDDK == NULL) {
			TRACE( "OpenService()ʧ�ܣ�ԭ��=%d\n", GetLastError() );
			goto BExit;
		} else {
			TRACE( "OpenService()�ɹ�\n");
		}
	} else {
		TRACE( "CreateService()�ɹ�\n");
	}

	bool ret = ::StartService(hServiceDDK, NULL, NULL);	//�����������
	if (ret == false) {
		TRACE( "StartService()ʧ�ܣ���������Ѿ�������ԭ��=%d\n", GetLastError() );
	}
	bRet = true;

BExit:	//�뿪ǰ��Ӧ����
	if(hServiceDDK) {
		CloseServiceHandle(hServiceDDK);
	}
	if(hServiceMgr) {
		CloseServiceHandle(hServiceMgr);
	}
	return bRet;
}


bool CDriverLoaderDlg::UnloadDriver(void)
{
	bool bRet = false;
	SC_HANDLE hSCM=NULL;		//SCM�������ľ��,�������OpenSCManager�ķ���ֵ
	SC_HANDLE hService=NULL;	//NT��������ķ��������������OpenService�ķ���ֵ
	SERVICE_STATUS SvrSta;

	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  //��SCM������
	if( hSCM == NULL ) {
		TRACE( "OpenSCManager() ʧ�� %d ! \n", GetLastError());  
		goto BeforeLeave;
	} else {
		TRACE( "OpenSCManager() �ɹ� ! \n" );  
	}

	hService = OpenService( hSCM, m_drivername, SERVICE_ALL_ACCESS);  //����������Ӧ�ķ���
	if( hService == NULL )  {
		TRACE( "OpenService() ʧ�� %d ! \n", GetLastError() );  
		goto BeforeLeave;
	} else {  
		TRACE( "OpenService() �ɹ� ! \n" );
	} 

	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) ) {		//ֹͣ�����������ֹͣʧ�ܣ�ֻ�������������ܣ��ٶ�̬����
		TRACE( "��ControlService() ֹͣ��������ʧ�� :%d !\n", GetLastError() );  
	}  else  {
		TRACE( "��ControlService() ֹͣ��������ɹ� !\n" );  
	}  
	
	if( !DeleteService( hService ) ) {		//��̬ж����������
		TRACE( "ж��ʧ��:DeleteSrevice()�����:%d !\n", GetLastError() );  
	}  else  {  
		TRACE ( "ж�سɹ� !\n" );  
	}  
	bRet = true;

BeforeLeave:		//�뿪ǰ�رմ򿪵ľ��
	if(hService>0) {
		CloseServiceHandle(hService);
	}
	if(hSCM>0) {
		CloseServiceHandle(hSCM);
	}
	return bRet;
}
