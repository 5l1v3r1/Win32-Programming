
// TestSQL.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestSQLApp:
// �йش����ʵ�֣������ TestSQL.cpp
//

class CTestSQLApp : public CWinApp
{
public:
	CTestSQLApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestSQLApp theApp;