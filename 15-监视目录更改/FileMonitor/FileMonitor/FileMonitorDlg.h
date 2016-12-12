
// FileMonitorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CFileMonitorDlg �Ի���
class CFileMonitorDlg : public CDialogEx
{
// ����
public:
	CFileMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILEMONITOR_DIALOG };

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
	CListBox listbox;
	afx_msg void OnBnClickedButtonChoosefile();
	afx_msg void OnBnClickedButtonStart();
	CButton button_start;
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonExit();
};
