// WinSocket.cpp : �������̨Ӧ�ó������ڵ㡣
//

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

SOCKADDR_IN clientsin;
SOCKET mysocket;
int len;

DWORD WINAPI mythreads(LPVOID lpParam) {
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
	return 0;
}

int main()
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
	mysocket=socket(AF_INET, SOCK_STREAM, 0);

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

	len = sizeof(SOCKADDR_IN);

	HANDLE handles[5];	//�߳���
	for (int i = 0; i < 5; i++)
		handles[i] = CreateThread(NULL, 0, mythreads, NULL, 0, NULL);
	::WaitForMultipleObjects(5, handles, true, INFINITE);

	//9���˳�ʱ�� WSACleanupж���׽ӿ�
	WSACleanup();


	return 0;
}

