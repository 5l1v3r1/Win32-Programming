#include <iostream>
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

/*
	UDP�ͻ��˼ܹ�����
	1�� //��ʼ���׽��ֻ���WSAStartup		
	2�� //��ʼ����ַ�Ͷ˿�
	3�� //����UDP�׽���socket		 
	4�� //��sendto��������
	5�� //��recvfrom��������
*/

int main() {
	cout << "�뷢��Client��Ϣ: " << endl;

	//	1.��ʼ���׽��ֻ���WSAStartup		
	WSADATA wsdata;
	int ret = WSAStartup(MAKEWORD(2,2), &wsdata);
	if (ret != 0) {
		cout << "��ʼ��ʧ��" << endl;
		return -1;
	}

	//2.��ʼ����ַ�Ͷ˿�
	SOCKET MyClient= socket(AF_INET,SOCK_DGRAM, 0);
	if (ret == INVALID_SOCKET) {
		cout << "�����׽���ʧ��" << endl;
		return -1;
	}

	//3.��SOCKADDR������UDP�׽���socket
	SOCKADDR_IN ServerAddr, ClientAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	ServerAddr.sin_port=htons(1234);

	while (true) {
		char sendbuff[256];
		gets(sendbuff);
		 //4.��sendto��������	return 0;
		sendto(MyClient, sendbuff, 255, 0,(sockaddr*)&ServerAddr, sizeof(ServerAddr));

		//5.��recvfrom��������
		char buff[256];
		int len = sizeof(ServerAddr);
		recvfrom(MyClient, buff, 255, 0, (sockaddr*)&ServerAddr, &len);
		if (ret == SOCKET_ERROR) {
			cout << "��������ʧ��" << endl;
			closesocket(MyClient);
			WSACleanup();
			return -1;
		}
		UINT uip=ServerAddr.sin_addr.S_un.S_addr;
		printf("�յ���Ϣ��%s\t������:d.%d.%d,%d \n",buff,LOBYTE(uip),HIBYTE(uip),LOBYTE(HIWORD(uip)),HIBYTE(HIWORD(uip)));
	}
	return 0;
}