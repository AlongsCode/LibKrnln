#pragma warning(disable:4996)
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include"文本转换.h"
KrnlnApi bool 端口检测(unsigned short port, const std::string& ip_address)
{
	bool result = false;
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0)
	{
		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		addrinfo* addr_result;
		if (getaddrinfo(ip_address.c_str(), std::to_string(port).c_str(), &hints, &addr_result) == 0)
		{
			SOCKET sock = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);
			if (sock != INVALID_SOCKET)
			{
				if (connect(sock, addr_result->ai_addr, (int)addr_result->ai_addrlen) != SOCKET_ERROR)
				{
					result = true;
				}
				closesocket(sock);
			}
			freeaddrinfo(addr_result);
		}
		WSACleanup();
	}
	return result;
}

KrnlnApi bool 端口检测(unsigned short port, const std::wstring& ip_address)
{
	bool result = false;
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0)
	{
		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		addrinfo* addr_result;
		if (getaddrinfo(宽文本到文本(ip_address).c_str(), std::to_string(port).c_str(), &hints, &addr_result) == 0)
		{
			SOCKET sock = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);
			if (sock != INVALID_SOCKET)
			{
				if (connect(sock, addr_result->ai_addr, (int)addr_result->ai_addrlen) != SOCKET_ERROR)
				{
					result = true;
				}
				closesocket(sock);
			}
			freeaddrinfo(addr_result);
		}
		WSACleanup();
	}
	return result;
}