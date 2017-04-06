
// DriverLoaderDlg.h : ͷ�ļ�
//

#pragma once


// CDriverLoaderDlg �Ի���
class CDriverLoaderDlg : public CDialogEx
{
// ����
public:
	CDriverLoaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRIVERLOADER_DIALOG };

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
	afx_msg void OnBnClickedButtonSrc();
	CString cs_src;
	afx_msg void OnBnClickedButtonLoad();
	CString m_drivername;
	CString m_driverpath;
	bool LoadDriver(void);
	afx_msg void OnBnClickedButtonUnload();
	bool UnloadDriver(void);
};
