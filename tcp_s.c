#include < winsock2.h >
#include < stdio.h >
#include <string.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

void ErrorMessage(char *str);

void main()
{	
	WSADATA wsaData;
	SOCKET hTCPsock;
	SOCKET hClientsock;

	SOCKADDR_IN servAddr;
	SOCKADDR_IN ClientAddr;

	char *servPort = "12345";
	char msg[BUFSIZE];
	int StrLen;	
	int ClientAddrSize;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorMessage("WSAStartup() Error");


	hTCPsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (hTCPsock == INVALID_SOCKET)   ErrorMessage("hTCPscok Error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(servPort));

	if (bind(hTCPsock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorMessage("Bind Error");


	printf("%d ��Ʈ�� �ּ� �Ҵ��� �Ǿ����ϴ�.\n", ntohs(servAddr.sin_port));

	if (listen(hTCPsock, 5) == SOCKET_ERROR)   ErrorMessage("Listen Error");

	printf("IP �ּ� : %s\n", inet_ntoa(servAddr.sin_addr));
	printf("���� ������Դϴ�.\n");

	while (1)
	{
		ClientAddrSize = sizeof(ClientAddr);
		hClientsock = accept(hTCPsock, (SOCKADDR*)&ClientAddr, &ClientAddrSize);

		printf("���ӵ� Ŭ���̾�Ʈ : %s\n", inet_ntoa(ClientAddr.sin_addr));
		printf("���ӵ� Ŭ���̾�Ʈ ��Ʈ : %d\n", htons(ClientAddr.sin_port));
		
		while (StrLen = recv(hClientsock, msg, BUFSIZE, 0))
		{
			msg[StrLen] = 0;

			if (stricmp(msg, "q") == 0){
				printf("���ӵ� %s Ŭ���̾�Ʈ�� ����Ǿ����ϴ�.\n", inet_ntoa(ClientAddr.sin_addr));
				break;
			}

			send(hClientsock, msg, StrLen, 0);
		}

		closesocket(hClientsock);
	}

	closesocket(hTCPsock);
	WSACleanup();
}

void ErrorMessage(char *str)
{
	printf("%s\n", str);
}
