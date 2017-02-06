
// Socket_ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "Socket_ClientDlg.h"
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


// CSocket_ClientDlg �Ի���




CSocket_ClientDlg::CSocket_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocket_ClientDlg::IDD, pParent)
	, m_csIP(_T(""))
	, m_nPORT(0)
	, m_csMESSAGE(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocket_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPORT);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnCONNECT);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSEND);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnCLOSE);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_csMESSAGE);
	DDX_Control(pDX, IDC_LIST_SEND, m_listSEND);
	DDX_Control(pDX, IDC_LIST_RECV, m_listRECV);
}

BEGIN_MESSAGE_MAP(CSocket_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSocket_ClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocket_ClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSocket_ClientDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CSocket_ClientDlg ��Ϣ�������

BOOL CSocket_ClientDlg::OnInitDialog()
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
	m_ClientSocket.SetDlg(this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSocket_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocket_ClientDlg::OnPaint()
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
HCURSOR CSocket_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSocket_ClientDlg::OnClose() {		//�����ڳ�Ա�������Ա����ת��
	m_ClientSocket.Close();
	m_btnCONNECT.EnableWindow(true);
	m_btnSEND.EnableWindow(false);
	m_btnCLOSE.EnableWindow(false);
}
void CSocket_ClientDlg::OnReceive() {		//�����ڳ�Ա�������Ա����ת��
	char buff[256] = {0};
	int retnum = m_ClientSocket.Receive(buff, 256);
	if (retnum) {			//�ܵ������ֽ���Ŀ����0
		CString cs;
		cs.Format(L"%s", buff);
		m_listRECV.AddString(cs);
		UpdateData(false);
	}
}

void CSocket_ClientDlg::OnBnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_ClientSocket.Create()) {
		if (m_ClientSocket.Connect(m_csIP, m_nPORT)) {
			TRACE("���ӳɹ�\n");
			m_btnCONNECT.EnableWindow(false);
			m_btnSEND.EnableWindow(true);
			m_btnCLOSE.EnableWindow(true);
		} else {
			m_ClientSocket.Close();
		}
	}
}


void CSocket_ClientDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (!m_csMESSAGE.IsEmpty()) {
		int sendlen = m_ClientSocket.Send(m_csMESSAGE,m_csMESSAGE.GetLength()*2);
		if (sendlen > 0) {
			TRACE("�ͻ��˳ɹ�����%d �ֽ�\n",sendlen);
			m_listSEND.AddString(m_csMESSAGE);
			m_csMESSAGE.Empty();
		}
	}
	UpdateData(false);
}


void CSocket_ClientDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnClose();
}
