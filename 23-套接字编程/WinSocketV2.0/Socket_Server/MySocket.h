#pragma once

// CMySocket ����Ŀ��

class CSocket_ServerDlg; //��ǰ����CSocket_ServerDlg��

class CMySocket : public CSocket	//�����Լ����׽�����
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept( int nErrorCode );
	void SetDlg(CSocket_ServerDlg *dest);
private:
	CSocket_ServerDlg *m_pdlg;
};


