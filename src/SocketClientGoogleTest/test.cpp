#include "gtest/gtest.h"

#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "../../src/SocketClientLib/SocketClient.h"

class TestSocketClient : public ::testing::Test {

protected:

	void SetUp() override {

		setlocale(0, "");

		socket.StartUp();

		socket.AddrInfoConfigure(ip, port);

		socket.SocketInit();

		socket.Connect();

		msgLenght = socket.SendMsg(sendMsg);

		socket.Shutdown();

		socket.RecieveMsg();

		strcpy_s(recvMsg, sizeof(recvMsg), socket.GetRecvMsg());

	}

	//void TearDown() {}

	SocketClient socket;

	char* sendMsg = "Hello World!";
	char recvMsg[256];

	char ip[256] = "45.79.112.203";
	char port[16] = "4242";

	int msgLenght;

};

TEST_F(TestSocketClient, StrEquality) {

	ASSERT_STREQ(sendMsg, recvMsg);
	
}

TEST_F(TestSocketClient, SizeEquality) {

	ASSERT_EQ(strlen(sendMsg), strlen(recvMsg));

}