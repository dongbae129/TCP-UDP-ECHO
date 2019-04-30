#include < winsock2.h >
#include < stdio.h >
#include <string.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

void ErrorMessage(char *str);

void main()
{	
	WSADATA wsadata;
	SOCKET h_s_socket;
	SOCKET h_c_socket;

	SOCKADDR_IN servAddr;
	SOCKADDR_IN clientAddr;

	char *servPort = "12345";
	char * str = "This is ECHO operate";
	char msg[BUFSIZE];
	int strLen;	
	int c_addrsize;

	
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		ErrorMessage("WSAStartup() Error");


	h_s_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (h_s_socket == INVALID_SOCKET)   ErrorMessage("h_s_socket Error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(servPort));

	if (bind(h_s_socket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorMessage("Bind Error");


	printf("포트번호 : %d.\n", ntohs(servAddr.sin_port));
	

	if (listen(h_s_socket, 5) == SOCKET_ERROR)   ErrorMessage("Listen Error");

	printf("IP 주소 : %s\n", inet_ntoa(servAddr.sin_addr));
	printf("서버 대기중.\n");
	

	while (1)
	{
		c_addrsize = sizeof(clientAddr);
		h_c_socket = accept(h_s_socket, (SOCKADDR*)&clientAddr, &c_addrsize);

		printf("접속된 클라이언트 : %s\n", inet_ntoa(clientAddr.sin_addr));
		printf("접속된 클라이언트 포트 : %d\n", ntohs(clientAddr.sin_port));
		send(h_c_socket, str, strlen(str), 0);
		
		while (strLen = recv(h_c_socket, msg, BUFSIZE, 0))
		{
			msg[strLen] = 0;
			printf("받은 문자 : %s \n", msg);
			if (stricmp(msg, "exit") == 0){
				printf("클라이언트 %s 종료.\n", inet_ntoa(clientAddr.sin_addr));
				break;
			}

			send(h_c_socket, msg, strLen, 0);
		}

		closesocket(h_c_socket);
	}

	closesocket(h_s_socket);
	WSACleanup();
}

void ErrorMessage(char *str)
{
	printf("%s\n", str);
}
