
// DriverLoader.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDriverLoaderApp:
// �йش����ʵ�֣������ DriverLoader.cpp
//

class CDriverLoaderApp : public CWinApp
{
public:
	CDriverLoaderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDriverLoaderApp theApp;