#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include<windows.h>
#pragma comment(lib,"Ws2_32.lib")
#else
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif // DEBUG






std::vector<std::string> GetIp()
{
	std::vector < std::string> ip_addresses;

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) == 0)
	{
		hostent* host_entry = gethostbyname(hostname);
		if (host_entry)
		{
			for (int i = 0; host_entry->h_addr_list[i] != nullptr; ++i)
			{
				in_addr* address = reinterpret_cast<in_addr*>(host_entry->h_addr_list[i]);
				ip_addresses.emplace_back(inet_ntoa(*address));
			}
			std::reverse(ip_addresses.begin(), ip_addresses.end());
		}
		else
		{
			std::cerr << "gethostname failed: " << strerror(errno) << std::endl;
		}


	}
	return ip_addresses;
}
