cmake_minimum_required(VERSION 3.26)

project(SocketClientLib)

enable_testing()

set(Sources
	SocketClient.cpp
)

set(Headers
	SocketClient.h
	Sock_Exc.h
)

add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})