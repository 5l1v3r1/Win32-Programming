
// Socket_Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSocket_ClientApp:
// �йش����ʵ�֣������ Socket_Client.cpp
//

class CSocket_ClientApp : public CWinApp
{
public:
	CSocket_ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSocket_ClientApp theApp;