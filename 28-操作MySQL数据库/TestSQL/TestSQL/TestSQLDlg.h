
// TestSQLDlg.h : ͷ�ļ�
//

#pragma once


// CTestSQLDlg �Ի���
class CTestSQLDlg : public CDialogEx
{
// ����
public:
	CTestSQLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTSQL_DIALOG };

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
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonExe();
	CString cs_sql;
	afx_msg void OnBnClickedButtonClear();
};
