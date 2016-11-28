// ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// C������Dlg �Ի���




C������Dlg::C������Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C������Dlg::IDD, pParent)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(C������Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &C������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &C������Dlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &C������Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &C������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C������Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C������Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C������Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C������Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C������Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &C������Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C������Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON13, &C������Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON11, &C������Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &C������Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON10, &C������Dlg::OnBnClickedButton10)
	ON_EN_CHANGE(IDC_EDIT1, &C������Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON14, &C������Dlg::OnBnClickedButton14)
END_MESSAGE_MAP()


// C������Dlg ��Ϣ�������

BOOL C������Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
		CDialog::OnSysCommand(nID, lParam);
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

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR C������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}










///////////////////���㹦��

double expr(char* str);
const int MAX=80;              //�����������ַ�������
void eatspace(char* str){       //ȥ���ո� 
    int i=0;
    int j=0;
    while(str[i]!='\0')
        if(str[i]==' '){                
            i++;
        }
        else{
            str[j]=str[i];
            i++; 
            j++;
        }
    str[j]='\0';

}
char* extract(char* str,int& index){        //��������֮���expr
    int count=1;
    char* substr=NULL;
    int substr_begin=index;
    int substr_end=index;
    char buffer[MAX];

    while(str[index]!='\0'){
        buffer[index-substr_begin]=str[index];

        switch(str[index++]){
        case '(': count++; break;
        case ')': 
            count--; 
            substr_end=index-1;
            int length=substr_end-substr_begin;
            if(0==count){
                 buffer[length]='\0';
                 substr=new char[length+1];
                 if(!substr){
					 ::MessageBox(NULL,"�ڴ�������", "����", MB_ICONERROR);
					exit(0);
                 }
                 else{
                     strcpy(substr,buffer);
                     return substr;
                 }
            }
           
            break;
        }
    }
    if(count>0){
		 ::MessageBox(NULL,"���Ų�ƥ��", "����", MB_ICONERROR);
		exit(0);
    }

    
            
}
double number(char* str,int& index){       //����number
    double value=0.0;
    double factor=1.0;
    if(str[index]=='('){
        char* psubstr=NULL;
        psubstr=extract(str,++index);
        value=expr(psubstr);
        delete[] psubstr;
        psubstr=NULL;
        return value;
    }

    if(!isdigit(str[index])){
		 ::MessageBox(NULL,"���벻�Ϸ�", "����", MB_ICONERROR);
		exit(0);
    }
    while(isdigit(str[index])){
        value=10*value+(str[index++]-'0');
    }
    if(str[index]!='.'){
        return value;
    }
    else{
        while(isdigit(str[++index])){
            factor*=0.1;
            value+=(str[index]-'0')*factor;
        }
    }

    return value;

}
double term(char* str,int& index){        //����term
    double value=0.0;
    value=number(str,index);

    while(true){
        switch(str[index++]){
        case '*': value*=number(str,index);  break;
        case '/': value-=number(str,index);   break;
        default: index--; return value;
        }
    }

}
double expr(char* str){          //����expr
    double value=0.0;    
    int index=0;

    value=term(str,index);
    while(true){
        switch(str[index++]){
        case '+': value+=term(str,index); break;
        case '-': value-=term(str,index); break;
        case '\0': return value;
		 ::MessageBox(NULL,"���ʽ����", "����", MB_OK);
        }
    }
    return value;

}

//////////////////////////////
#include <stdio.h>
void C������Dlg::OnBnClickedOk()
{
    char *buffer = m_text.GetBuffer();
    eatspace(buffer);
	int result = expr(buffer);
	char buff[250];
	sprintf(buff, "%d",  result);
	m_text = buff;
	UpdateData(false);
    //cout<<expr(buffer)<<endl;

	//char *exp = 
	//char postexp[MaxSize];
	//trans(exp, postexp);
	//int rtn = computevalue(postexp);
	//char buff[2500];
	//sprintf(buff, "%d",  rtn);
	//m_text = buff;
	//UpdateData(false);
}


void C������Dlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}

void C������Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_text += L"1";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton2()
{
	m_text += L"2";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton3()
{
	m_text += L"3";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton4()
{
	m_text += L"4";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton5()
{
	m_text += L"5";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton6()
{
	m_text += L"6";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton7()
{
	m_text += L"7";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton8()
{
	m_text += L"8";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton9()
{
	m_text += L"9";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton13()
{
	m_text += L"+";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton11()
{
	m_text += L"-";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton12()
{
	m_text += L"*";
	UpdateData(false);
}

void C������Dlg::OnBnClickedButton10()
{
	m_text += L"/";
	UpdateData(false);
}

void C������Dlg::OnBnClickedOk2()
{
	m_text = L"";
	UpdateData(false);
}



void C������Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void C������Dlg::OnBnClickedButton14()
{
	m_text += L"0";
	UpdateData(false);
}
