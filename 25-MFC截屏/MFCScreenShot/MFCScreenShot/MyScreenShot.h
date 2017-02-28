
class ScreenDlg;

class MyScreenShot {
	private:
		POINT pfirst, pnext;		//��¼�϶���������
		POINT pstart;		//����õ������ϽǵĶ���
		ScreenDlg *dlg;	//������ָ��
	public:
		bool ispress;				//��¼�Ƿ������
		WCHAR path[255];		//����·��
		MyScreenShot();			//��ʼ��
		void SetDlg(ScreenDlg *wnddlg);		//����������ָ��
		void HideSelf();			//���ش���
		void ShowSelf();			//��ʾ����
		void SetWindowShape();			//���ô����м�͸��
		void DrawFrame();		//���ƿ��
		void EraseFrame();		//��ȥ���
		bool IsSamePoint(POINT pcheck);		//�ж����λ���Ƿ�ֹ
		void UpdatePoint();		//�������λ��
		void CheckPoint();		//�������λ��
		void TakePic(char filename[]);	//��ͼ
		void SavePic();				//����ͼƬ
};
