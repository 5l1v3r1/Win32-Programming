#include "stdafx.h"
#include "MFCScreenshot.h"
#include "MyScreenShot.h"
#include "ScreenDlg.h"
#include <atlconv.h>
extern WCHAR savedir[255];

MyScreenShot::MyScreenShot() {
	dlg = NULL;
	ispress = false;
}
void MyScreenShot::SetDlg(ScreenDlg *wnddlg) {
	this->dlg = wnddlg;
}
void MyScreenShot::HideSelf() {
	SetWindowLong(dlg->GetParent()->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->GetParent()->m_hWnd, NULL, 0, LWA_ALPHA);
	SetWindowLong(dlg->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->m_hWnd, NULL, 150, LWA_ALPHA);
	SendMessage(dlg->m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
	SetWindowPos(dlg->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
}
void MyScreenShot::ShowSelf() {
	SetWindowLong(dlg->GetParent()->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->GetParent()->m_hWnd, NULL, 255, LWA_ALPHA);
}
void MyScreenShot::SetWindowShape() {
		CRgn rgndlg, rgnout;
		RECT rectdlg;
		dlg->GetWindowRect(&rectdlg);
		if (ispress) {
			int dlgwidth = rectdlg.right - rectdlg.left;
			int dlgheight = rectdlg.bottom - rectdlg.top;
			int outwidth = abs(pfirst.x - pnext.x);
			int outheight = abs(pfirst.y - pnext.y);
			CheckPoint();
			rgndlg.CreateRectRgn(rectdlg.left, rectdlg.top, rectdlg.right,rectdlg.bottom);
			rgnout.CreateRectRgn(pstart.x, pstart.y, pstart.x+outwidth, pstart.y+outheight);
			//�ϲ�
			rgndlg.CombineRgn(&rgndlg,&rgnout,RGN_DIFF);
			dlg->SetWindowRgn(rgndlg, true);
		} else {
			dlg->SetWindowRgn(rgndlg, true);
		}
		rgndlg.DeleteObject();
		rgnout.DeleteObject();
}
void MyScreenShot::DrawFrame() {
	HDC hdc = ::GetWindowDC(dlg->m_hWnd);
	HPEN hpen = ::CreatePen(PS_SOLID, 5, RGB(255,0,0));
	HPEN holdpen = (HPEN)::SelectObject(hdc, hpen);

	::MoveToEx(hdc, pfirst.x, pfirst.y, NULL);
	::LineTo(hdc, pnext.x, pfirst.y);
	::LineTo(hdc, pnext.x, pnext.y);
	::LineTo(hdc, pfirst.x, pnext.y);
	::LineTo(hdc, pfirst.x, pfirst.y);
	SetWindowShape();

	::SelectObject(hdc, holdpen);
	::DeleteObject(hpen);
	::ReleaseDC(dlg->m_hWnd, hdc);
}
void MyScreenShot::EraseFrame() {
	dlg->RedrawWindow();
}
bool MyScreenShot::IsSamePoint(POINT pcheck) {
	return (pcheck.x == pnext.x && pcheck.y == pnext.y);
}
void MyScreenShot::UpdatePoint() {
	if (ispress)
		::GetCursorPos(&pnext);
	else
		::GetCursorPos(&pfirst);
}
void MyScreenShot::CheckPoint() {
	if (pnext.x <= pfirst.x && pnext.y <= pfirst.y) {			//�����ϵ�����
		pstart.x = pnext.x;
		pstart.y = pnext.y;
	} else if (pnext.x > pfirst.x && pnext.y <= pfirst.y) {	//�����ϵ�����
		pstart.x = pfirst.x;
		pstart.y = pnext.y;
	} else if (pnext.x > pfirst.x && pnext.y > pfirst.y) {		//�����ϵ�����
		pstart.x = pfirst.x;
		pstart.y = pfirst.y;
	} else {				//�����ϵ�����
		pstart.x = pnext.x;
		pstart.y = pfirst.y;
	}
}
void MyScreenShot::TakePic(char filename[]) {
    CDC *pDC;//��ĻDC
    pDC = CDC::FromHandle(GetDC(NULL));//��ȡ��ǰ������ĻDC
    int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//�����ɫģʽ
	int Width = abs(pfirst.x-pnext.x);
    int Height = abs(pfirst.y-pnext.y);
    CDC memDC;//�ڴ�DC
    memDC.CreateCompatibleDC(pDC);
    
	CheckPoint();

    CBitmap memBitmap, *oldmemBitmap;//��������Ļ���ݵ�bitmap
    memBitmap.CreateCompatibleBitmap(pDC, Width, Height);
    oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC
    memDC.BitBlt(0, 0, Width, Height, pDC, pstart.x, pstart.y, SRCCOPY);//������Ļͼ���ڴ�DC

    //���´��뱣��memDC�е�λͼ���ļ�
    BITMAP bmp;
    memBitmap.GetBitmap(&bmp);//���λͼ��Ϣ  
    FILE *fp = fopen(filename, "w+b");

    BITMAPINFOHEADER bih = {0};//λͼ��Ϣͷ
    bih.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С
    bih.biCompression = BI_RGB;
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С
    bih.biWidth = bmp.bmWidth;//���
    bih.biHeight = bmp.bmHeight;//�߶�

    BITMAPFILEHEADER bfh = {0};//λͼ�ļ�ͷ
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ 
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//�����ڴ汣��λͼ����
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p, 
        (LPBITMAPINFO) &bih, DIB_RGB_COLORS);//��ȡλͼ����
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//д��λͼ����
    delete [] p;
    fclose(fp);
    memDC.SelectObject(oldmemBitmap);
}

void MyScreenShot::SavePic() {
	SetWindowLong(dlg->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->m_hWnd, NULL, 0, LWA_ALPHA);

	time_t t;
	time(&t);
	tm *timeinfo=localtime(&t);
	WCHAR wbuff[500];
	WCHAR wtime[500];
	wsprintf(wbuff, savedir);
	wsprintf(wtime, L"\\[��ͼ]%02d��%02d��%02d��%02dʱ%02d��%02d��.bmp",timeinfo->tm_year+1900,timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	wcscat(wbuff, wtime);
	USES_CONVERSION ;
	TakePic(W2A(wbuff));

	SetWindowLong(dlg->m_hWnd,GWL_EXSTYLE, 0x80000);
	::SetLayeredWindowAttributes(dlg->m_hWnd, NULL, 100, LWA_ALPHA);
}