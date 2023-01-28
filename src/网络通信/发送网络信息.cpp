#pragma warning(disable:4996)
#include <WS2tcpip.h>
#include<vector>
#include<string>
#include"文本转换.h"
KrnlnApi bool 发送网络信息(const std::string& serverIP, u_short port, const std::vector<unsigned char> data) {
	//初始化
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}

	// 创建 socket
	SOCKET sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);


	//判断是否是IPv4

	if (inet_pton(AF_INET, serverIP.data(), &server.sin_addr) == 1) {
		//IPV4不做特殊处理
	}
	else {
		sockaddr_in6 server6;
		server6.sin6_family = AF_INET6;
		server6.sin6_port = htons(port);
		//判断是否是IPv6
		if (InetPtonA(AF_INET6, serverIP.data(), &server6.sin6_addr) == 1) {
			server = reinterpret_cast<sockaddr_in&>(server6);
		}
		else {
			closesocket(sock);
			WSACleanup();
			return false;
		}
	}

	// 连接
	if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// 发送
	int iSendResult = send(sock, reinterpret_cast<char*>(const_cast<unsigned char*>(data.data())), static_cast<int>(data.size()), 0);
	if (iSendResult == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// 释放资源
	closesocket(sock);
	WSACleanup();
	return true;
}

KrnlnApi bool 发送网络信息(const std::wstring& WserverIP, u_short port, const std::vector<unsigned char> data) {
	std::string serverIP = 宽文本到文本(WserverIP);
	//初始化
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}

	// 创建 socket
	SOCKET sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);


	//判断是否是IPv4

	if (inet_pton(AF_INET, serverIP.data(), &server.sin_addr) == 1) {
		//IPV4不做特殊处理
	}
	else {
		sockaddr_in6 server6;
		server6.sin6_family = AF_INET6;
		server6.sin6_port = htons(port);
		//判断是否是IPv6
		if (InetPtonA(AF_INET6, serverIP.data(), &server6.sin6_addr) == 1) {
			server = reinterpret_cast<sockaddr_in&>(server6);
		}
		else {
			closesocket(sock);
			WSACleanup();
			return false;
		}
	}

	// 连接
	if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// 发送
	int iSendResult = send(sock, reinterpret_cast<char*>(const_cast<unsigned char*>(data.data())), static_cast<int>(data.size()), 0);
	if (iSendResult == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// 释放资源
	closesocket(sock);
	WSACleanup();
	return true;
}