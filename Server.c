#include < winsock2.h >
#include < stdio.h >
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

void ErrorMessage(char *str);

void main()
{
	WSADATA wsadata;
	SOCKET h_s_socket;
	SOCKADDR_IN servAddr;
	SOCKADDR_IN clientAddr;

	char *servPort = "12345";
	char msg[BUFSIZE];
	int strLen;
	int c_addrsize;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		ErrorMessage("WSAStartup() Error");

	h_s_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (h_s_socket == INVALID_SOCKET)
		ErrorMessage("h_s_socket Error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(servPort));

	if (bind(h_s_socket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorMessage("Bind Error");

	printf("포트 번호 : %d\n", ntohs(servAddr.sin_port));
	printf("IP 주소 : %s\n", inet_ntoa(servAddr.sin_addr));
	printf("서버 대기중.\n");

	while (1)
	{
		c_addrsize = sizeof(clientAddr);
		
		strLen = recvfrom(h_s_socket, msg, BUFSIZE, 0, (SOCKADDR*)&clientAddr, &c_addrsize);
		msg[strLen] = 0;
		printf("받은 문자 : %s \n", msg);
		sendto(h_s_socket, msg, strLen, 0, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
	}

	closesocket(h_s_socket);
	WSACleanup();
}

void ErrorMessage(char *str)
{
	printf("%s\n", str);
}