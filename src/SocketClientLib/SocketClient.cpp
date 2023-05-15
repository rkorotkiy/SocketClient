#include "SocketClient.h"

SocketClient::SocketClient() {

}

SocketClient::SocketClient(SocketClient& other) {
	wsaData = other.wsaData;
	hints = other.hints;
	addrResult = other.addrResult;
	ConnectSocket = other.ConnectSocket;
}

void SocketClient::StartUp() {

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0) {
		throw RetVal(result);
	}

}

void SocketClient::AddrInfoConfigure(char* ipAddr, char* port) {

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int result = getaddrinfo(ipAddr, port, &hints, &addrResult);

	if (result != 0) {
		throw RetVal(result);
	}

}

void SocketClient::SocketInit() {

	ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		throw RetVal(ConnectSocket);
	}
}

void SocketClient::Connect() {

	int result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	//if (result == SOCKET_ERROR) {
	//	std::cout << "Unable to connect to server" << std::endl;
	//	closesocket(ConnectSocket);
	//	ConnectSocket = INVALID_SOCKET;
	//	freeaddrinfo(addrResult);
	//	WSACleanup();
	//	return 1;
	//}

	if (result == SOCKET_ERROR) {
		throw RetVal(ConnectSocket);
	}

}

int SocketClient::SendMsg(char* msg) {

	strcpy_s(sendBuffer, sizeof(sendBuffer), msg);

	int result = send(ConnectSocket, sendBuffer, (int)strlen(sendBuffer), NULL);
	ZeroMemory(sendBuffer, sizeof(sendBuffer));
	//if (result == SOCKET_ERROR) {
	//	std::cout << "send failed, error: " << result << std::endl;
	//	closesocket(ConnectSocket);
	//	freeaddrinfo(addrResult);
	//	WSACleanup();
	//	return 1;
	//}

	if (result == SOCKET_ERROR) {
		throw RetVal(result);
	}

	return result;

}

void SocketClient::Shutdown() {

	int result = shutdown(ConnectSocket, SD_SEND);
	/*	if (result == SOCKET_ERROR) {
			std::cout << "Shutdown error: " << result << std::endl;
			closesocket(ConnectSocket);
			freeaddrinfo(addrResult);
			WSACleanup();
			return 1;
		}*/

	if (result == SOCKET_ERROR) {
		throw RetVal(result);
	}

}

int SocketClient::RecieveMsg() {

	//do {
	ZeroMemory(recvBuffer, sizeof(recvBuffer));
	int result = recv(ConnectSocket, recvBuffer, sizeof(recvBuffer), NULL);

	/*	if (result > 0) {
			std::cout << "Recieved " << result << " bytes" << std::endl;
			std::cout << "Recieved data: " << recvBuffer << std::endl;
		}
		else if (result == 0) {
			std::cout << "Connection closed" << std::endl;
		}
		else {
			std::cout << "recv failed with error" << std::endl;
		}*/
		//} while (result > 0);

	return result;

}

char* SocketClient::GetRecvMsg() {
	return recvBuffer;
}

SocketClient::~SocketClient() {
	closesocket(ConnectSocket);
	freeaddrinfo(addrResult);
	WSACleanup();
}