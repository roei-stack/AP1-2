cmake_minimum_required(VERSION 3.20)
project(ass2)

set(CMAKE_CXX_STANDARD 11)

include_directories(Server/classifying)

add_executable(TcpServer Server/TcpServer.cpp
        Server/Sockets/Socket.h
        Server/Sockets/Socket.cpp
        Server/Sockets/SocketStrategy.h
        Server/Sockets/Tcp.h
        Server/Sockets/Tcp.cpp
        Server/Sockets/Udp.h
        Server/Sockets/Udp.cpp)

add_executable(UdpServer Server/UdpServer.cpp
        Server/Sockets/Socket.h
        Server/Sockets/Socket.cpp
        Server/Sockets/SocketStrategy.h
        Server/Sockets/Tcp.h
        Server/Sockets/Tcp.cpp
        Server/Sockets/Udp.h
        Server/Sockets/Udp.cpp)

add_executable(Client Client.cpp
        Server/Sockets/Socket.h
        Server/Sockets/Socket.cpp
        Server/Sockets/SocketStrategy.h
        Server/Sockets/Tcp.h
        Server/Sockets/Tcp.cpp
        Server/Sockets/Udp.h
        Server/Sockets/Udp.cpp)

add_executable(test1 Server/Sockets/SocketStrategy.h Server/Sockets/Tcp.cpp Server/Sockets/Tcp.h Server/Sockets/Udp.cpp Server/Sockets/Udp.h Server/testingsockets/tcpServerTest.cpp Server/Sockets/Socket.cpp Server/Sockets/Socket.h)
add_executable(test2 Server/Sockets/SocketStrategy.h Server/Sockets/Tcp.cpp Server/Sockets/Tcp.h Server/Sockets/Udp.cpp Server/Sockets/Udp.h Server/testingsockets/tcpClientTest.cpp Server/Sockets/Socket.cpp Server/Sockets/Socket.h)
