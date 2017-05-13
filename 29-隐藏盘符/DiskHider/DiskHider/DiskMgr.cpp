#include "StdAfx.h"
#include "DiskHider.h"
#include "DiskMgr.h"
#include "DiskHiderDlg.h"

DiskMgr::DiskMgr(CDiskHiderDlg* dlg) {
	this->dlg = dlg;
	ShowDisks();
	Getinformation();
}

void DiskMgr::Getinformation() {
	int disknum = dlg->m_disks.GetCount();
	for (int i = 0; i < disknum; i++) {
		CString DiskName;
		WCHAR DosPath[MAX_PATH];  
		dlg->m_disks.GetLBText(i, DiskName);
		QueryDosDevice(DiskName.Left(DiskName.GetLength()-1), DosPath, MAX_PATH);
		DiskNames[i] = DiskName.Left(DiskName.GetAllocLength()-1);
		DosPaths[i] = DosPath;
	}
}

void DiskMgr::ShowDisks() {
	WCHAR buff[MAX_PATH];
	CString cs_disks;
	DWORD len;
	len = ::GetLogicalDriveStrings(MAX_PATH, buff);
	for (int i = 0; i < len; i++) {
		if (buff[i] == 0 ) {
			if (buff[i+1] == 0 ) {
				break;
			} else {
				dlg->m_disks.AddString(cs_disks);
				cs_disks = "";
			}
		} else {
			cs_disks += buff[i];
		}
	}
	dlg->m_disks.SetCurSel(0);
}

bool DiskMgr::HideVolume(WCHAR *Disk) {
	// �ȱ�����Ϣ
	//SaveInformation(Disk);
	// ���̷���Dos�豸·���Ƴ�
	WCHAR szDeviceName[MAX_PATH] = {0};
	::lstrcpy(szDeviceName, Disk);
	szDeviceName[2] = '\0';
	if (!::DefineDosDevice(DDD_REMOVE_DEFINITION, szDeviceName, NULL)) {
		return FALSE;
	}
	// ж�ؾ���ص�
	if (!::DeleteVolumeMountPoint(Disk)) {
		return FALSE;
	}
	return TRUE;
}

void DiskMgr::ShowAllVolume() {
	int disknum = dlg->m_disks.GetCount();
	for (int i = 0; i < disknum; i++) {
		ShowVolume(DiskNames[i].GetBuffer(), DosPaths[i].GetBuffer());
	}
}

bool DiskMgr::ShowVolume(LPWSTR lpwDeviceName, LPWSTR lpwDosPath) {  
	if(!::DefineDosDevice(DDD_RAW_TARGET_PATH, lpwDeviceName, lpwDosPath)) {
		return FALSE;
	}

	WCHAR szUniqueVolumeName[MAX_PATH] = {0};
	CString DiskName = lpwDeviceName;
	DiskName.Append(L"\\");
	// ��ȡװ�ص���
	if (!GetVolumeNameForVolumeMountPoint(DiskName, szUniqueVolumeName, MAX_PATH))
	{
		szUniqueVolumeName[0] = 0;
	}
	
	// ���̷���Dos�豸·������
	if (!::DefineDosDevice(DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION |DDD_EXACT_MATCH_ON_REMOVE, lpwDeviceName, lpwDosPath)) {
		return FALSE;
	}

	// ���þ�װ�ص�
	//	::MessageBox(NULL, szUniqueVolumeName, szDriver, MB_OK);
	/* ע����ʹ��SetVolumeMountPoint��ʱ�򣬹��ص�Ŀ¼������ڣ����ұ���Ϊ��Ŀ¼��������������ʧ�� */
	::SetVolumeMountPoint(DiskName, szUniqueVolumeName);
}