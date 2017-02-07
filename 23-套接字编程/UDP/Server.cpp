#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

/*
	UDP�׽��ַ���˼ܹ�����:
	1�� //��ʼ���׽��ֻ���WSAStartup		
	2�� //��ʼ����ַ�Ͷ˿�
	3�� //��SOCKADDR������UDP�׽���socket		 
	4�� //��recvfrom��������
	5�� //��sendto��������
	6�� //�˳����߷��ص�5������	

*/

int main() {
	cout << "Server��:" << endl;

	//	1.��ʼ���׽��ֻ���WSAStartup		
	WSADATA wsdata;
	int ret = WSAStartup(MAKEWORD(2,2), &wsdata);
	if (ret != 0) {
		cout << "��ʼ��ʧ��" << endl;
		return -1;
	}

	//2.��ʼ����ַ�Ͷ˿�
	SOCKET MyServer= socket(AF_INET,SOCK_DGRAM, 0);
	if (ret == INVALID_SOCKET) {
		cout << "�����׽���ʧ��" << endl;
		return -1;
	}

	//3.��SOCKADDR������UDP�׽���socket
	SOCKADDR_IN ServerAddr, ClientAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	ServerAddr.sin_port=htons(1234);
	ret = bind(MyServer, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (ret == SOCKET_ERROR) {
		cout << "���׽���ʧ��" << endl;
		closesocket(MyServer);
		WSACleanup();
		return -1;
	}

	 //4.��recvfrom��������
	while (true) {
		char buff[256];
		int len = sizeof(ClientAddr);
		recvfrom(MyServer, buff, 255, 0, (sockaddr*)&ClientAddr, &len);
		if (ret == SOCKET_ERROR) {
			cout << "��������ʧ��" << endl;
			closesocket(MyServer);
			return -1;
		}
		UINT uip=ClientAddr.sin_addr.S_un.S_addr;
		printf("�յ���Ϣ��%s\t������:d.%d.%d,%d \n",buff,LOBYTE(uip),HIBYTE(uip),LOBYTE(HIWORD(uip)),HIBYTE(HIWORD(uip)));


		 //5.��sendto��������	return 0;
		char sendbuff[256] = "��������get������";
		sendto(MyServer, sendbuff, 255, 0,(sockaddr*)&ClientAddr, len);

		 //6.�˳����߷��ص�5������	}
	}
	getchar();
	return 0;
}