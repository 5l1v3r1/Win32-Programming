
// Socket_ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Socket_Server.h"
#include "Socket_ServerDlg.h"
#include "afxdialogex.h"

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


// CSocket_ServerDlg �Ի���




CSocket_ServerDlg::CSocket_ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocket_ServerDlg::IDD, pParent)
	, m_csIP(_T(""))
	, m_nPORT(0)
	, m_csMESSAGE(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocket_ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IP, m_editIP);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPORT);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPORT);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_csMESSAGE);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_editMESSAGE);
	DDX_Control(pDX, IDC_LIST_SEND, m_listSEND);
	DDX_Control(pDX, IDC_LIST_RECV, m_listRECV);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnLISTEN);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSEND);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnCLOSE);
}

BEGIN_MESSAGE_MAP(CSocket_ServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CSocket_ServerDlg::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocket_ServerDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSocket_ServerDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CSocket_ServerDlg ��Ϣ�������

BOOL CSocket_ServerDlg::OnInitDialog()
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
	m_nPORT = 1234;
	m_csIP = _T("127.0.0.1");
	UpdateData(false);
	m_ServerSocket.SetDlg(this);	//�������ڲ�m_pdlgָ��ָ��������
	m_ClientSocket.SetDlg(this);	//�������ڲ�m_pdlgָ��ָ��������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSocket_ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocket_ServerDlg::OnPaint()
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
HCURSOR CSocket_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocket_ServerDlg::OnBnClickedButtonListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_ServerSocket.Create(m_nPORT)) {		//�����׽���,Ĭ����TCPЭ��󶨱���
		TRACE("����˴����׽��ֳɹ�\n");
		if (m_ServerSocket.Listen()) {
			TRACE("����˼����ɹ�\n");
			m_btnLISTEN.EnableWindow(false);
			m_btnCLOSE.EnableWindow(true);
		}
	}
}

void CSocket_ServerDlg::OnClose() {
	//�رտͻ����׽���
	m_ClientSocket.Close();
}

void CSocket_ServerDlg::OnReceive() {
	char buff[256] = {0};
	int retnum = m_ClientSocket.Receive(buff, 256);
	if (retnum) {			//�ܵ������ֽ���Ŀ����0
		CString cs;
		cs.Format(L"%s", buff);
		m_listRECV.AddString(cs);
		UpdateData(false);
	}
}
void CSocket_ServerDlg::OnAccept() {
	m_ServerSocket.Accept(m_ClientSocket);	//��ʼ��m_ClientSocket��������ͻ����շ���Ϣ
	m_btnSEND.EnableWindow(true);
	m_btnCLOSE.EnableWindow(true);
}


void CSocket_ServerDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (!m_csMESSAGE.IsEmpty()) {
		int sendlen = m_ClientSocket.Send(m_csMESSAGE,m_csMESSAGE.GetLength()*2);
		if (sendlen > 0) {
			TRACE("����˳ɹ�����%d �ֽ�\n",sendlen);
			m_listSEND.AddString(m_csMESSAGE);
			m_csMESSAGE.Empty();
		}
	}
	UpdateData(false);
}


void CSocket_ServerDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ServerSocket.Close();
	OnClose();
	TRACE("����˹ر�");
	m_btnLISTEN.EnableWindow(true);
	m_btnSEND.EnableWindow(false);
	m_btnCLOSE.EnableWindow(false);
}
