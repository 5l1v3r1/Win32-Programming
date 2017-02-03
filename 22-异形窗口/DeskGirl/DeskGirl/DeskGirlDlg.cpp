
// DeskGirlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeskGirl.h"
#include "DeskGirlDlg.h"
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


// CDeskGirlDlg �Ի���




CDeskGirlDlg::CDeskGirlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeskGirlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeskGirlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GIRL, m_girl);
}

BEGIN_MESSAGE_MAP(CDeskGirlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


int flag = 0;
CStatic *pgirl;
CBitmap mybitmap1;
CBitmap mybitmap2;
CBitmap mybitmap3;
#define MY_TIMER 1234
VOID CALLBACK eyes(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) {
	if (flag == 0) {
		pgirl->SetBitmap(mybitmap1);
	} else if (flag == 14) {
		pgirl->SetBitmap(mybitmap2);
	} else if (flag == 15) {
		pgirl->SetBitmap(mybitmap3);
	}
	flag = (flag+1)%16;
}


// CDeskGirlDlg ��Ϣ�������

BOOL CDeskGirlDlg::OnInitDialog()
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
	pgirl = &m_girl;
	CBitmap bmpdlg;
	bmpdlg.LoadBitmap(IDB_BITMAP_DLG);

	CDC *pdc=GetWindowDC();
	CDC cdc;
	cdc.CreateCompatibleDC(pdc);
	cdc.SelectObject(&bmpdlg);

	CRect rect;
	CRgn rgn, temprgn;
	GetClientRect(&rect);
	rgn.CreateRectRgnIndirect(rect);
	int width = rect.Width();
	int height = rect.Height();
	COLORREF del = cdc.GetPixel(0, 0);
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			if (cdc.GetPixel(x, y)==del) {
				temprgn.CreateRectRgn(x,y,x+1,y+1);
				rgn.CombineRgn(&rgn, &temprgn, RGN_XOR);
				temprgn.DeleteObject();
			}
		}
	SetWindowRgn(rgn, true);
	mybitmap1.LoadBitmap(IDB_BITMAP2);
	mybitmap2.LoadBitmap(IDB_BITMAP3);
	mybitmap3.LoadBitmap(IDB_BITMAP4);
	::SetTimer(NULL, MY_TIMER, 150, eyes);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDeskGirlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDeskGirlDlg::OnPaint()
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
HCURSOR CDeskGirlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDeskGirlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}

