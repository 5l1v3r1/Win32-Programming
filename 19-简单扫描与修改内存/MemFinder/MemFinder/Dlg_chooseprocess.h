#pragma once
#include "afxcmn.h"


// CDlg_chooseprocess �Ի���

class CDlg_chooseprocess : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_chooseprocess)

public:
	CDlg_chooseprocess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_chooseprocess();

// �Ի�������
	enum { IDD = IDD_CHOOSEPROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl list_process;
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
