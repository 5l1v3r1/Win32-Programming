#pragma once


// CDllDialog �Ի���

class CDllDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDllDialog)

public:
	CDllDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDllDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
