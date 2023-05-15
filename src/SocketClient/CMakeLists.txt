cmake_minimum_required(VERSION 3.26)

project(SocketClient)

set(Sources
	Source.cpp
)

add_executable(${PROJECT_NAME} ${Sources})

target_link_libraries(${PROJECT_NAME} PUBLIC SocketClientLib)