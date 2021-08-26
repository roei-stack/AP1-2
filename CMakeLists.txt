cmake_minimum_required(VERSION 3.16)
project(ass2)

set(CMAKE_CXX_STANDARD 11)

include_directories(classification sockets)

add_executable(TcpServer
        sockets/TcpSocket.cpp sockets/TcpSocket.h sockets/TcpServerSocket.cpp sockets/TcpServerSocket.h
        classification/Reader.cpp classification/Iris.cpp classification/KnnClassifier.h servers/TcpServer.cpp
        servers/Server.cpp)

add_executable(UdpServer
        sockets/UdpServerSocket.cpp sockets/UdpServerSocket.h sockets/UdpSocket.cpp sockets/UdpSocket.h servers/Server.cpp servers/Server.h
        classification/Reader.cpp classification/Iris.cpp classification/KnnClassifier.h servers/UdpServer.cpp)

add_executable(Client client/Client.cpp
        sockets/UdpSocket.cpp sockets/TcpSocket.cpp)

