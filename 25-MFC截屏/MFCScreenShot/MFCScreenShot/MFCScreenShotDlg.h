
// MFCScreenShotDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCScreenShotDlg �Ի���
class CMFCScreenShotDlg : public CDialogEx
{
// ����
public:
	CMFCScreenShotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCSCREENSHOT_DIALOG };

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
	CString m_cs_path;
	CButton m_btn_start;
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();
};
