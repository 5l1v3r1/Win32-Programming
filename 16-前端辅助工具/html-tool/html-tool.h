
// html-tool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// ChtmltoolApp:
// �йش����ʵ�֣������ html-tool.cpp
//

class ChtmltoolApp : public CWinApp
{
public:
	ChtmltoolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern ChtmltoolApp theApp;