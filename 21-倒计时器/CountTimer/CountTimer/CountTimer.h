
// CountTimer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCountTimerApp:
// �йش����ʵ�֣������ CountTimer.cpp
//

class CCountTimerApp : public CWinApp
{
public:
	CCountTimerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCountTimerApp theApp;