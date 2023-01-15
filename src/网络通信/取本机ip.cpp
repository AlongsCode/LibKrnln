#include <string>

#ifdef _WIN32
#include<windows.h>
#pragma comment(lib,"Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <locale>
#include <codecvt>
#endif 


#ifdef _WIN32

KrnlnApi std::wstring 取本机IPW() {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return L"";
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return L"";
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
	std::string localIP;
	localIP.assign(inet_ntoa(addr));
	WSACleanup();
	int widesize = MultiByteToWideChar(CP_ACP, 0, localIP.c_str(), -1, NULL, 0);
	if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	wchar_t* resultstring = new wchar_t[widesize];

	int convresult = MultiByteToWideChar(CP_ACP, 0, localIP.c_str(), -1, resultstring, widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	std::wstring wstrReturn(resultstring);
	delete[] resultstring;
	return wstrReturn;
}

KrnlnApi std::string 取本机IPA() {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return "";
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return "";
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
	std::string localIP;
	localIP.assign(inet_ntoa(addr));
	WSACleanup();
	return localIP;
}

#else

KrnlnApi std::string 取本机IPA() {
	struct addrinfo hints, * info, * p;
	int gai_result;

	char hostname[256];
	gethostname(hostname, sizeof(hostname));

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME;

	if ((gai_result = getaddrinfo(hostname, NULL, &hints, &info)) != 0) {
		return "";
	}

	for (p = info; p != NULL; p = p->ai_next) {
		if (p->ai_family == AF_INET) {
			struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
			char ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(ipv4->sin_addr), ip, INET_ADDRSTRLEN);
			freeaddrinfo(info);
			return ip;
		}
		else if (p->ai_family == AF_INET6) {
			struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
			char ip[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, &(ipv6->sin6_addr), ip, INET6_ADDRSTRLEN);
			freeaddrinfo(info);
			return ip;
		}
	}

	freeaddrinfo(info);
	return "";
}

std::wstring 取本机IPW() {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string local_ip = 取本机IPA();
	return converter.from_bytes(local_ip);
}


#endif 


