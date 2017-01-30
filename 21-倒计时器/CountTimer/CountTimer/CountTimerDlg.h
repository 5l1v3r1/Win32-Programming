
// CountTimerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCountTimerDlg �Ի���
class CCountTimerDlg : public CDialogEx
{
// ����
public:
	CCountTimerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COUNTTIMER_DIALOG };

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
	CButton start;
	CButton pause;
	CButton stop;
	afx_msg void OnBnClickedButtonStart();
	CString cs_time;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CString cs_counttime;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonPause();
};
