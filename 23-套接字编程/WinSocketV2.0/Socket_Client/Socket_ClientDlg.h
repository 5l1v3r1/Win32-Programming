
// Socket_ClientDlg.h : ͷ�ļ�
//
#include "MySocket.h"
#pragma once


// CSocket_ClientDlg �Ի���
class CSocket_ClientDlg : public CDialogEx
{
// ����
public:
	CSocket_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKET_CLIENT_DIALOG };

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
	CString m_csIP;
	UINT m_nPORT;
	CMySocket m_ClientSocket;
	CButton m_btnCONNECT;
	CButton m_btnSEND;
	CButton m_btnCLOSE;
	void OnClose();		//�����ڳ�Ա�������Ա����ת��
	void OnReceive();		//�����ڳ�Ա�������Ա����ת��
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	CString m_csMESSAGE;
	CListBox m_listSEND;
	CListBox m_listRECV;
	afx_msg void OnBnClickedButtonClose();
};
