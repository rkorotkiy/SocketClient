#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "ws2_32.lib")

#include <stdexcept>
#include <iostream>
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Sock_Exc.h"

class SocketClient {
private:

	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	SOCKET ConnectSocket = INVALID_SOCKET;

	char sendBuffer[512] = "";
	char recvBuffer[512] = "";

public:

	SocketClient();
	SocketClient(SocketClient& other);

	void StartUp();

	void AddrInfoConfigure(char* ipAddr, char* port);

	void SocketInit();

	void Connect();

	int SendMsg(char* msg);

	void Shutdown();

	int RecieveMsg();

	char* GetRecvMsg();

	~SocketClient();

};

#endif