
// DeskGirlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CDeskGirlDlg �Ի���
class CDeskGirlDlg : public CDialogEx
{
// ����
public:
	CDeskGirlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DESKGIRL_DIALOG };

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CStatic m_girl;
//	afx_msg void OnBnClickedButtonTest();
};
