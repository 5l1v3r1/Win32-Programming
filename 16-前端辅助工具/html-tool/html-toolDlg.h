
// html-toolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ChtmltoolDlg �Ի���
class ChtmltoolDlg : public CDialogEx
{
// ����
public:
	ChtmltoolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HTMLTOOL_DIALOG };

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
	CString m_red;
	CString m_green;
	CString m_blue;
protected:
	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
public:
	CSliderCtrl m_slider;
	afx_msg void OnTRBNThumbPosChangingSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CButton button_opacity;
	afx_msg void OnBnClickedButtonOpacity();
	CButton m_fresh;
	afx_msg void OnBnClickedButtonFresh();
	CButton m_choosefile;
	afx_msg void OnBnClickedButtonChoosefile();
};
