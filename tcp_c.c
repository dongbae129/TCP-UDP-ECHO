#include < winsock2.h >
#include < stdio.h >
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 1024

void ErrorMessage(char *str);

void main()
{
	WSADATA wsadata;
	SOCKET h_socket;
	SOCKADDR_IN servAddr;

	char s_address[100];
	char s_port[100];
	int r_addrsize; 
	char msg[BUFSIZE];
	

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		ErrorMessage("WSAStartup() Error");


	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (h_socket == INVALID_SOCKET)   ErrorMessage("h_socket error");

	printf("연결할 주소(IP)를 입력하세요 :");
	gets(s_address);

	printf("연결할 포트를 입력하세요 :");
	gets(s_port);



	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(s_address);
	servAddr.sin_port = ntohs(atoi(s_port));

	if (connect(h_socket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorMessage("Connect Error");

	printf("접속된 클라이언트 : %s\n", inet_ntoa(servAddr.sin_addr));

	r_addrsize = recv(h_socket, msg, BUFSIZE, 0);
	msg[r_addrsize] = 0;
	printf("%s \n", msg);
	puts("exit is break");
	while (1)
	{
		printf("SEND : ");
		gets(msg);

		send(h_socket, msg, strlen(msg), 0);

		if (stricmp(msg, "exit") == 0) break;

		r_addrsize = recv(h_socket, msg, BUFSIZE, 0);
		msg[r_addrsize] = 0;
		printf("RECV : %s\n", msg);
	}

	WSACleanup();
}


void ErrorMessage(char *str)
{
	printf("%s\n", str);
}
