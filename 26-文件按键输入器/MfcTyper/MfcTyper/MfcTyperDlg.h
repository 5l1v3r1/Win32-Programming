
// MfcTyperDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMfcTyperDlg �Ի���
class CMfcTyperDlg : public CDialogEx
{
// ����
public:
	CMfcTyperDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTYPER_DIALOG };

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
	CButton btn_file;
	CButton btn_start;
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonStart();
	CString cs_path;
};
