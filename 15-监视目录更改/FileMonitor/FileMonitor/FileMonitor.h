
// FileMonitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileMonitorApp:
// �йش����ʵ�֣������ FileMonitor.cpp
//

class CFileMonitorApp : public CWinApp
{
public:
	CFileMonitorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileMonitorApp theApp;