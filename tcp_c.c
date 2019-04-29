#include < winsock2.h >
#include < stdio.h >
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 1024

void ErrorMessage(char *str);

void main()
{
	WSADATA wsaData;
	SOCKET hTCPsock;
	SOCKADDR_IN servAddr;
	char addr1[100];
	char servPort[100];
	int recvSize;
	char msg[BUFSIZE];
	

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorMessage("WSAStartup() Error");


	hTCPsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (hTCPsock == INVALID_SOCKET)   ErrorMessage("hTCPscok Error");

	printf("연결할 주소(IP)를 입력하세요 :");
	gets(addr1);

	printf("연결할 포트를 입력하세요 :");
	gets(servPort);



	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(addr1);
	servAddr.sin_port = ntohs(atoi(servPort));

	if (connect(hTCPsock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorMessage("Connect Error");

	printf("접속된 클라이언트 : %s\n", inet_ntoa(servAddr.sin_addr));
	
	while (1)
	{
		printf("SEND : ");
		gets(msg);

		send(hTCPsock, msg, strlen(msg), 0);

		if (stricmp(msg, "q") == 0) break;

		recvSize = recv(hTCPsock, msg, BUFSIZE, 0);
		msg[recvSize] = 0;
		printf("RECV : %s\n", msg);
	}

	WSACleanup();
}


void ErrorMessage(char *str)
{
	printf("%s\n", str);
}
