
// Socket_ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"

// CSocket_ServerDlg �Ի���
class CSocket_ServerDlg : public CDialogEx
{
// ����
public:
	CSocket_ServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKET_SERVER_DIALOG };

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
	CEdit m_editIP;
	CString m_csIP;
	CEdit m_editPORT;
	UINT m_nPORT;
	CString m_csMESSAGE;
	CEdit m_editMESSAGE;
	CListBox m_listSEND;
	CListBox m_listRECV;
	CButton m_btnLISTEN;
	CButton m_btnSEND;
	CButton m_btnCLOSE;
	afx_msg void OnBnClickedButtonListen();
	CMySocket m_ServerSocket;	//������׽���
	CMySocket m_ClientSocket;	//�������׽���

	void OnClose();		//�����ڳ�Ա�������Ա����ת��
	void OnReceive();		//�����ڳ�Ա�������Ա����ת��
	void OnAccept();		//�����ڳ�Ա�������Ա����ת��
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
};
