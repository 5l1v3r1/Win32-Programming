// mfcDLL.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "mfcDLL.h"
#include "DllDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CmfcDLLApp

BEGIN_MESSAGE_MAP(CmfcDLLApp, CWinApp)
END_MESSAGE_MAP()


// CmfcDLLApp ����

CmfcDLLApp::CmfcDLLApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmfcDLLApp ����

CmfcDLLApp theApp;


void ShowDlg() {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	//DLL�е�MFC���õĺ궨��
	CDllDialog dlg;	//��ʾDLL�еĴ���
	dlg.DoModal();
}


// CmfcDLLApp ��ʼ��

BOOL CmfcDLLApp::InitInstance()
{
	CWinApp::InitInstance();
	//����DLLʱ�ĳ�ʼ��
	TRACE("�Ѽ���DLL\n");
	ShowDlg();
	return TRUE;
}


int CmfcDLLApp::ExitInstance()
{
	//�˳�DLLʱ�ĳ�ʼ��
	TRACE("��ж��DLL\n");
	return CWinApp::ExitInstance();
}


