
// Socket_Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSocket_ServerApp:
// �йش����ʵ�֣������ Socket_Server.cpp
//

class CSocket_ServerApp : public CWinApp
{
public:
	CSocket_ServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSocket_ServerApp theApp;