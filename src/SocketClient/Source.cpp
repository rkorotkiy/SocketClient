#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "../SocketClientLib/SocketClient.h"

int main() {

	setlocale(0, "");

	SocketClient socket;

	socket.StartUp();

	char ip[256] = "45.79.112.203";
	char port[16] = "4242";

	socket.AddrInfoConfigure(ip, port);
	
	socket.SocketInit();

	socket.Connect();

	char sendMsg[256];

	std::cout << "Введите сообщение: " << std::endl;
	std::cin >> sendMsg;

	int msgLenght;

	msgLenght = socket.SendMsg(sendMsg);

	std::cout << msgLenght << " Bytes sent" << std::endl;

	socket.Shutdown();

	socket.RecieveMsg();

	std::cout << socket.GetRecvMsg();

	return 0;

}







































//int main(){
//
//	setlocale(0, "Rus");
//
//	WSADATA wsaData;
//	ADDRINFO hints;
//	ADDRINFO* addrResult = NULL;
//	SOCKET ConnectSocket = INVALID_SOCKET;
//
//	char sendBuffer[512];
//	char recvBuffer[512];
//
//	int result;
//
//	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (result != 0) {
//		std::cout << "WSAStartup failed, result = " << result << std::endl;
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	result = getaddrinfo("45.79.112.203", "4242", &hints, &addrResult);
//	if (result != 0) {
//		std::cout << "getaddrinfo failed with error: " << result << std::endl;
//		WSACleanup();
//		return 1;
//	}
//
//	ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
//	if (ConnectSocket == INVALID_SOCKET) {
//		std::cout << "Socket creation failed" << std::endl;
//		freeaddrinfo(addrResult);
//		WSACleanup();
//		return 1;
//	}
//
//	result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
//	if (result == SOCKET_ERROR) {
//		std::cout << "Unable to connect to server" << std::endl;
//		closesocket(ConnectSocket);
//		ConnectSocket = INVALID_SOCKET;
//		freeaddrinfo(addrResult);
//		WSACleanup();
//		return 1;
//	}
//
//	std::cout << "Введите сообщение: ";
//	std::cin >> sendBuffer;
//
//	result = send(ConnectSocket, sendBuffer, (int)strlen(sendBuffer), NULL);
//	ZeroMemory(sendBuffer, sizeof(sendBuffer));
//	if (result == SOCKET_ERROR) {
//		std::cout << "send failed, error: " << result << std::endl;
//		closesocket(ConnectSocket);
//		freeaddrinfo(addrResult);
//		WSACleanup();
//		return 1;
//	}
//
//	std::cout << "Sent: " << result << "bytes" << std::endl;
//
//	result = shutdown(ConnectSocket, SD_SEND);
//	if (result == SOCKET_ERROR) {
//		std::cout << "Shutdown error: " << result << std::endl;
//		closesocket(ConnectSocket);
//		freeaddrinfo(addrResult);
//		WSACleanup();
//		return 1;
//	}
//
//	do {
//		ZeroMemory(recvBuffer, sizeof(recvBuffer));
//		result = recv(ConnectSocket, recvBuffer, sizeof(recvBuffer), NULL);
//		if (result > 0) {
//			std::cout << "Recieved " << result << " bytes" << std::endl;
//			std::cout << "Recieved data: " << recvBuffer << std::endl;
//		}
//		else if (result == 0) {
//			std::cout << "Connection closed" << std::endl;
//		}
//		else {
//			std::cout << "recv failed with error" << std::endl;
//		}
//	} while (result > 0);
//
//	closesocket(ConnectSocket);
//	freeaddrinfo(addrResult);
//	WSACleanup();
//
//	system("pause");
//
//	return 0;
//
//}