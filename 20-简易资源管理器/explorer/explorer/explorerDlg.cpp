
// explorerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "explorer.h"
#include "explorerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CexplorerDlg �Ի���




CexplorerDlg::CexplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CexplorerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CexplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, tree);
	DDX_Control(pDX, IDC_LIST1, files);
}

BEGIN_MESSAGE_MAP(CexplorerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, &CexplorerDlg::OnTvnItemexpandingTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CexplorerDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CexplorerDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CexplorerDlg ��Ϣ�������

BOOL CexplorerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
/////////////////////////////////////////////////////////////
	HTREEITEM hrootc= tree.InsertItem(L"C:");
	HTREEITEM hrootd= tree.InsertItem(L"D:");
	HTREEITEM hroote= tree.InsertItem(L"E:");
	HTREEITEM hrootf= tree.InsertItem(L"F:");
	HTREEITEM hrootg= tree.InsertItem(L"G:");
	imglist.Create(16,16, ILC_MASK | ILC_COLOR32, 0, 0);
	tree.SetImageList(&imglist, TVSIL_NORMAL);
	dfs(L"C://*.*", hrootc, 2);
	dfs(L"D://*.*", hrootd, 2);
	dfs(L"E://*.*", hroote, 2);
	dfs(L"F://*.*", hrootf, 2);
	dfs(L"G://*.*", hrootg, 2);
/////////////////////////////////////////////////////////////
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CexplorerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CexplorerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CexplorerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CexplorerDlg::dfs(CString path, HTREEITEM hroot, int next)		//�����������㲢���룬�Ա���ʾչ����ť(�ظ����ڱ���ǰӦɾ��)
{
	if(path.Right(4) != L"/*.*")
		path+=L"//*.*";
	CFileFind cfile;
	BOOL ret = cfile.FindFile(path);
	while (ret && next) {
		ret = cfile.FindNextFile();
		if (!cfile.IsDots() && cfile.IsDirectory()) {

			SHFILEINFO psfi;
			memset(&psfi,0,sizeof(psfi));
			::SHGetFileInfo(cfile.GetFilePath(), 0, &psfi, sizeof(psfi), SHGFI_ICON | SHGFI_TYPENAME );
			 
			HTREEITEM hnew = tree.InsertItem(cfile.GetFileName(), hroot); 
			TRACE(">>>>>>>>>");
			TRACE(cfile.GetFileName());
			TRACE("\n");
			tree.SetItemImage(hnew, imglist.Add(psfi.hIcon), 0);
			dfs(cfile.GetFilePath(), hnew, next-1);
		}
	}
}


void CexplorerDlg::OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	HTREEITEM hSubItem = pNMTreeView->itemNew.hItem;

	HTREEITEM hson = tree.GetChildItem(hSubItem);		//ɾ���ظ�
	while (hson != NULL) {
		tree.DeleteItem(hson);
		hson = tree.GetChildItem(hSubItem);
	}

	HTREEITEM hp =  tree.GetParentItem(hSubItem);
	CString path = tree.GetItemText(hSubItem);
	while (hp != NULL) {
		CString temp = tree.GetItemText(hp);
		path = temp +"\\"+path;
		hp =  tree.GetParentItem(hp);
	}
	dfs(path, hSubItem, 2);		//�ɸ��ṹ�õ�·��
}


void CexplorerDlg::showfiles(CString filepath)
{
	CFileFind cfindfile;
	imglist2.Create(32, 32, ILC_COLOR32|ILC_MASK, 0, 0);
	BOOL ret = cfindfile.FindFile(filepath);
	while (ret) {
		ret = cfindfile.FindNextFile();	//�����ڵ���֮ǰ GetFilePath����һ������ FindNextFile
		WCHAR path[255];
		wcscpy(path, cfindfile.GetFilePath().GetBuffer(255));

		SHFILEINFO psfi;
		memset(&psfi,0,sizeof(psfi));
		::SHGetFileInfo(path, 0, &psfi, sizeof(psfi), SHGFI_ICON);

		if (cfindfile.GetFileName() == "." || cfindfile.GetFileName() == "..")
			continue;

		imglist2.Add(psfi.hIcon);
		int sum = files.GetItemCount();
		files.InsertItem(sum, cfindfile.GetFileName(), sum);
	}
	files.SetImageList(&imglist2, LVSIL_NORMAL);

	cfindfile.Close();
}


void CexplorerDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hSubItem = tree.GetSelectedItem();
	HTREEITEM hp =  tree.GetParentItem(hSubItem);
	CString path = tree.GetItemText(hSubItem);
	while (hp != NULL) {
		CString temp = tree.GetItemText(hp);
		path = temp +"\\"+path;
		hp =  tree.GetParentItem(hp);
	}
	TRACE(path);
	TRACE("\n");
	files.DeleteAllItems();   //ɾ������
	showfiles(path+L"//*.*");

	*pResult = 0;
}


void CexplorerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = files.GetFirstSelectedItemPosition();
	if (pos) {
		int index = files.GetNextSelectedItem(pos);
		CString filename = files.GetItemText(index, 0);

		HTREEITEM hSubItem = tree.GetSelectedItem();
		HTREEITEM hp =  tree.GetParentItem(hSubItem);
		CString path = tree.GetItemText(hSubItem);
		while (hp != NULL) {
			CString temp = tree.GetItemText(hp);
			path = temp +"\\"+path;
			hp =  tree.GetParentItem(hp);
		}

		CString file = path + "\\" + filename;
		::ShellExecute(0, 0, file, 0, 0, SW_SHOWNORMAL);
	}
	*pResult = 0;
}
