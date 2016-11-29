
// ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"
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


// C������Dlg �Ի���




C������Dlg::C������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C������Dlg::IDD, pParent)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void C������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(C������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON14, &C������Dlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON13, &C������Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON5, &C������Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON15, &C������Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON1, &C������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &C������Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &C������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON16, &C������Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON3, &C������Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &C������Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &C������Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &C������Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &C������Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON10, &C������Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &C������Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON17, &C������Dlg::OnBnClickedButton17)
END_MESSAGE_MAP()


// C������Dlg ��Ϣ�������

BOOL C������Dlg::OnInitDialog()
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

void C������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C������Dlg::OnPaint()
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
HCURSOR C������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C������Dlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("1");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("2");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("3");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("4");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("5");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("6");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("+");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton16()
{
	m_text += _T("7");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("8");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("9");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("-");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("*");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("/");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += _T("0");
	UpdateData(false);
}


void C������Dlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text = _T("0");
	UpdateData(false);
}
///////////////////////////////////////////////////////////////////////////

class Calculator
{
public:
	Calculator(){};
	int getResult(std::string);
private:
	bool can_do(char c);
	void exe_cacu();
	void set(std::string);
	std::string exp;
	std::stack<int> number;
	std::stack<char> op;
};
void Calculator::set(std::string s)
{
	exp = s;
	while(!number.empty())	number.pop();
	while(!op.empty()) op.pop();
}
bool Calculator::can_do(char c)
{
	if(op.empty()) return false;
	if(op.top() == '(')	return false;
	if(c == '+' || c == '-')	return true;
	if(c == '*' && (op.top() == '*' || op.top() == '/'))	return true;
	if(c == '/' && (op.top() == '*' || op.top() == '/'))	return true;
	return false;
}

void Calculator::exe_cacu()
{
	int b = number.top();
	number.pop();
	int a = number.top();number.pop();
	int result;
	switch(op.top())
	{
	case '+':
		result = a+b;
		break;
	case '-':
		result = a-b;
		break;
	case '*':
		result = a*b;
		break;
	case '/': {
		if (b == 0) {
			::MessageBoxA(NULL, "���ִ���", "����", MB_ICONERROR);
			exit(0);
		}
		result = a/b;
		}
		break;
	}
	number.push(result);
	op.pop();
}


int Calculator::getResult(std::string s)
{
	set(s);
	int temp = 0;
	for(unsigned int i=0; i<exp.length(); i++)
	{
		if(isdigit(exp[i]))
		{
			temp = temp*10 + exp[i]-'0';
			if(i+1 == exp.length() || !isdigit(exp[i+1]))
			{
				number.push(temp);
				temp = 0;
			}
		}
		else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			if(can_do(exp[i]))
				exe_cacu();
			op.push(exp[i]);
		}
		else if(exp[i] == '(')
			op.push(exp[i]);
		else
		{
			while(op.top() != '(')
				exe_cacu();
			op.pop();
		}
	}
	while(!op.empty())
		exe_cacu();

	return number.top();
}
 std::string WStringToString(const std::wstring &wstr)
 {
     std::string str(wstr.length(), ' ');
     std::copy(wstr.begin(), wstr.end(), str.begin());
     return str; 
 }

 std::wstring StringToWString(const std::string &str)
 {
     std::wstring wstr(str.length(),L' ');
     std::copy(str.begin(), str.end(), wstr.begin());
     return wstr; 
 }

void C������Dlg::OnBnClickedButton17()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::wstring ws = m_text;
	m_text.ReleaseBuffer();
	std::string s;
	s = WStringToString(ws);
	char buff[100];
	Calculator calc;
	std::sprintf(buff, "%d", calc.getResult(s));
	m_text = buff;
	UpdateData(false);
}
