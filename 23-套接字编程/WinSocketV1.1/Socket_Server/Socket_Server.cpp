// WinSocket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>		//Ӧ����ͷ�ļ�WinSock2.h�Ϳ��ļ�ws2_32.lib

/*
		������ �˴��빹�����̣� 
		1�������׽��ֿ� ��WSAStartup��
		2�������׽��� ��socket��
		3�����׽��ְ󶨵�һ�����ص�ַ�Ͷ˿��ϣ�bind��
		4�����׽�����Ϊ����ģʽ��׼�����տͻ�����listen��
		5���ȴ��ͻ������������������󣬽����������󣬷���һ���µĶ�Ӧ�ڴ˴����ӵ��׽��֣�accept��
		6���÷��ص��׽��ֺͿͻ��˽���ͨ�ţ�send/recv��
		7�����أ��ȴ���һ�ͻ����� �ص���5��
		8���ر��׽��֡� closesocket
		9���˳�ʱ�� WSACleanupж���׽ӿ�
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

	//3�����׽��ְ󶨵�һ�����ص�ַ�Ͷ˿��ϣ�bind��
	SOCKADDR_IN sockin;
	sockin.sin_family = AF_INET;
	sockin.sin_port=htons(1234);		//ָ���˿�
	sockin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);		//���ð󶨵�ַINADDR_ANY
	
	//4�����׽�����Ϊ����ģ1234���տͻ�����listen��
	bind(mysocket, (sockaddr*)&sockin, sizeof(sockin));
	printf("�����������\n");

	//5���ȴ��ͻ������������������󣬽����������󣬷���һ���µĶ�Ӧ�ڴ˴����ӵ��׽��֣�accept��
	listen(mysocket, 4);
	SOCKADDR_IN clientsin;
	int len = sizeof(SOCKADDR_IN);
	while (true) {	//ѭ�������׽���
		SOCKET clientsocket = accept(mysocket, (SOCKADDR*)&clientsin, &len);		//����ͻ��˵��׽��־��clientsocket

		//6���÷��ص��׽��ֺͿͻ��˽���ͨ�ţ�send/recv��
		char buff[256] = {0};
		recv(clientsocket, buff, sizeof(buff), 0);
		printf("������յ���Ϣ:%s\n", buff);
		char buffret[] = "������Ѿ��յ���Ϣ��\n";
		send(clientsocket, buffret, sizeof(buffret), 0);
		//7�����أ���ȴ���һ�ͻ����� �ص���5��
		//8���ر��׽��֡� closesocket
		closesocket(clientsocket);
	}

	//9���˳�ʱ�� WSACleanupж���׽ӿ�
	WSACleanup();

	return 0;
}

