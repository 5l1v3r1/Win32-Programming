// DllDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcDLL.h"
#include "DllDialog.h"
#include "afxdialogex.h"


// CDllDialog �Ի���

IMPLEMENT_DYNAMIC(CDllDialog, CDialogEx)

CDllDialog::CDllDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDllDialog::IDD, pParent)
{

}

CDllDialog::~CDllDialog()
{
}

void CDllDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDllDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDllDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

// CDllDialog ��Ϣ�������


void CDllDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::MessageBox(NULL, L"�Ի���", L"DLL�Ի���", MB_ICONINFORMATION);
}
