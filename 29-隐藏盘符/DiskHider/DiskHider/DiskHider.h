
// DiskHider.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDiskHiderApp:
// �йش����ʵ�֣������ DiskHider.cpp
//

class CDiskHiderApp : public CWinApp
{
public:
	CDiskHiderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDiskHiderApp theApp;