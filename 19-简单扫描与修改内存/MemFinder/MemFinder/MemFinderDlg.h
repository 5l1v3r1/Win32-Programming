
// MemFinderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMemFinderDlg �Ի���
class CMemFinderDlg : public CDialogEx
{
// ����
public:
	CMemFinderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEMFINDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton radios_type;
	BOOL radios_value;
	afx_msg void OnBnClickedButtonChooseprocess();
	afx_msg void OnBnClickedButtonSearch();
	CString edit_processname;
	afx_msg void OnBnClickedButtonModify();
	CListCtrl list_memories;
	CString cs_value;
	afx_msg void OnBnClickedButtonSearch2();
};
