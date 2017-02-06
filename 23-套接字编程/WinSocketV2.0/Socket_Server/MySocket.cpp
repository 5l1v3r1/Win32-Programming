// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Socket_Server.h"
#include "MySocket.h"
#include "Socket_ServerDlg.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա���������ڳ�Ա���������ں������ڴ�����ʾ����
void CMySocket::OnClose(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("����˷��ֿͻ��ر��׽���\n");
		m_pdlg->OnClose();		//ת�������ڳ�Ա
	}
}
void CMySocket::OnReceive(int nErrorCode) {
	if (nErrorCode == 0) {
		TRACE("������յ��ͻ���Ϣ\n");
		m_pdlg->OnReceive();		//ת�������ڳ�Ա
	}
}
void CMySocket::OnAccept( int nErrorCode ) {
	if (nErrorCode == 0) {
		TRACE("����˷��ֿͻ�����\n");
		m_pdlg->OnAccept();		//ת�������ڳ�Ա
	}
}
void CMySocket::SetDlg(CSocket_ServerDlg *dest) {
	this->m_pdlg = dest;
}