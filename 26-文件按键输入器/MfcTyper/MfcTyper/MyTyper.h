
class CMfcTyperDlg;

class MyTyper {
	private:
		CMfcTyperDlg *pdlg;
	public:
		MyTyper();												//��ʼ��
		void SetDlg(CMfcTyperDlg *wnddlg);	//���öԻ���
		void Init();												//׼����ʼģ�ⰴ��
		void StartPrint();										//ģ�ⰴ��
};
