#include < winsock2.h >
#include < stdio.h >
#pragma comment(lib,"ws2_32.lib")


#define BUFSIZE 1024

void ErrorMessage(char *str);



void main()
{
	WSADATA wsadata;
	SOCKET h_socket;
	SOCKADDR_IN servAddr;

	int s_addrsize;
	char s_address[100];
	char s_port[100];
	char msg[BUFSIZE];
	int strLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) ErrorMessage("WSAStartup() Error");

	h_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (h_socket == INVALID_SOCKET)   ErrorMessage("h_socket Error");

	printf("연결할 주소(IP)를 입력하세요 :");
	gets(s_address);

	printf("연결할 포트를 입력하세요 :");
	gets(s_port);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(s_address);
	servAddr.sin_port = ntohs(atoi(s_port));

	printf("접속된 클라이언트 : %s\n", inet_ntoa(servAddr.sin_addr));
	printf("exit is break \n");
	while (1)
	{
		s_addrsize = sizeof(servAddr);

		printf("SEND : ");
		gets(msg);

		if (stricmp(msg, "exit") == 0) break;

		sendto(h_socket, msg, strlen(msg), 0, (SOCKADDR*)&servAddr, sizeof(servAddr));
		strLen = recvfrom(h_socket, msg, BUFSIZE, 0, (SOCKADDR*)&servAddr, &s_addrsize);

		msg[strLen] = 0;
		printf("RECV : %s\n", msg);
	}


	WSACleanup();
}



void ErrorMessage(char *str)
{
	printf("%s\n", str);
}