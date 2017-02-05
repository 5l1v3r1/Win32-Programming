// WinSocket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>		//Ӧ����ͷ�ļ�WinSock2.h�Ϳ��ļ�ws2_32.lib

/*
		�ͻ��� ����
		1�������׽��ֿ�  WSAStartup
		2�������׽��֣�socket��
		3���������������������connect��
		4���ͷ������˽���ͨ�ţ�send/recv��
		5���ر��׽��֡�closesocket
		6��ж���׽��ֿ� WSACleanup
*/


int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;	//�汾��
	WSADATA wsaData;	//����
	wVersionRequested = MAKEWORD( 2, 2 );

	//1�������׽��ֿ⣨WSAStartup��
	int err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		printf("��ʼ��ʧ��\n");
		getchar();
		return 0;
	}

	//2�������׽��֣�socket��
	SOCKET mysocket=socket(AF_INET, SOCK_STREAM, 0);

	//3���������������������connect��
	SOCKADDR_IN sockin;
	sockin.sin_family = AF_INET;
	sockin.sin_port=htons(1234);		//ָ���˿�
	sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//�󶨱�����������ַ127.0.0.1

	int ret = connect(mysocket, (SOCKADDR*)&sockin, sizeof(sockin));
	if (ret == SOCKET_ERROR) {
			printf("���ӷ�����ʧ��\n");
			getchar();
			return 0;
	}
	printf("���ӷ������ɹ�\n");

	//4���ͷ������˽���ͨ�ţ�send/recv��
	char mess[256];
	printf("�������˷�����Ϣ:");
	gets(mess);
	send(mysocket, mess, strlen(mess), 0);
	getchar();

	//5���ر��׽��֡�closesocket
	closesocket(mysocket);

	//6��ж���׽��ֿ� WSACleanup
	WSACleanup();

	return 0;
}

