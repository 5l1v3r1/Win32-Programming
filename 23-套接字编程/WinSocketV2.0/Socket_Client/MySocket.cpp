// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "MySocket.h"
#include "Socket_ClientDlg.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա���������ڳ�Ա���������ں������ڴ�����ʾ����
// CMySocket ��Ա���������ڳ�Ա���������ں������ڴ�����ʾ����
void CMySocket::OnClose(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("�ͻ��˹ر��׽���\n");
		m_pdlg->OnClose();		//ת�������ڳ�Ա
	}
}
void CMySocket::OnReceive(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("�ͻ����յ��������Ϣ\n");
		m_pdlg->OnReceive();		//ת�������ڳ�Ա
	}
}
void CMySocket::SetDlg(CSocket_ClientDlg *dest) {
	this->m_pdlg = dest;
}
