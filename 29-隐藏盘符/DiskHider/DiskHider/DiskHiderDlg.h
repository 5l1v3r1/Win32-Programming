
// DiskHiderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CDiskHiderDlg �Ի���
class CDiskHiderDlg : public CDialogEx
{
// ����
public:
	CDiskHiderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DISKHIDER_DIALOG };

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
	CComboBox m_disks;
	afx_msg void OnCbnSelchangeDisks();
	afx_msg void OnBnClickedButtonHide();
	afx_msg void OnBnClickedButtonRestore();
};
