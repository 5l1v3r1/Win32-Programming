
// MfcTyper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMfcTyperApp:
// �йش����ʵ�֣������ MfcTyper.cpp
//

class CMfcTyperApp : public CWinApp
{
public:
	CMfcTyperApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMfcTyperApp theApp;