// mfcDLL.h : mfcDLL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfcDLLApp
// �йش���ʵ�ֵ���Ϣ������� mfcDLL.cpp
//

class CmfcDLLApp : public CWinApp
{
public:
	CmfcDLLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
