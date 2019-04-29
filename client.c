#include < winsock2.h >
#include < stdio.h >
#pragma comment(lib,"ws2_32.lib")


#define BUFSIZE 1024

void ErrorMessage(char *str);



void main()
{
	WSADATA wsaData;
	SOCKET hSerSock;
	SOCKADDR_IN servAddr;
	int ServAddrSize;
	char addr1[100];
	char servPort[100];
	char msg[BUFSIZE];
	int StrLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) ErrorMessage("WSAStartup() Error");

	hSerSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (hSerSock == INVALID_SOCKET)   ErrorMessage("hTCPscok Error");

	printf("연결할 주소(IP)를 입력하세요 :");
	gets(addr1);

	printf("연결할 포트를 입력하세요 :");
	gets(servPort);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(addr1);
	servAddr.sin_port = ntohs(atoi(servPort));

	printf("접속된 클라이언트 : %s\n", inet_ntoa(servAddr.sin_addr));

	while (1)
	{
		ServAddrSize = sizeof(servAddr);

		printf("SEND : ");
		gets(msg);

		if (stricmp(msg, "q") == 0) break;

		sendto(hSerSock, msg, strlen(msg), 0, (SOCKADDR*)&servAddr, sizeof(servAddr));
		StrLen = recvfrom(hSerSock, msg, BUFSIZE, 0, (SOCKADDR*)&servAddr, &ServAddrSize);

		msg[StrLen] = 0;
		printf("RECV : %s\n", msg);
	}


	WSACleanup();
}



void ErrorMessage(char *str)
{
	printf("%s\n", str);
}