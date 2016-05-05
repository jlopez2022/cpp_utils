#include <iostream>
#include <cstring>      // Needed for memset

//include:  wsock32.lib and ws2_32.lib

#define __WIN32__
#undef UNICODE
#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <io.h>
#else
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_BSD_NETWORKING
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#endif

int main()
{

	int status;
	struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

									 // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
									 // to by hints must contain either 0 or a null pointer, as appropriate." When a struct 
									 // is created in C++, it will be given a block of memory. This memory is not necessary
									 // empty. Therefor we use the memset function to make sure all fields are NULL.     
	memset(&host_info, 0, sizeof host_info);


	WSADATA wsaData;
	status = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (status != 0) {
		std::cout << "\nError en WSA" << std::endl;
		getchar(); getchar();
		return 1;
	}



	std::cout << "\nSetting up the structs..." << std::endl;

	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
	host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

										 // Now fill up the linked list of host_info structs with google's address information.
	std::cout << "Reading from www.google.com\n";
	status = getaddrinfo("www.google.com", "80", &host_info, &host_info_list);
	// getaddrinfo returns 0 on succes, or some other value when an error occured.
	// (translated into human readable text by the gai_gai_strerror function).
	if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status);
	else std::cout << "OK" << std::endl;

	std::cout << "\n\nReading from www.google.lk\n";
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;
	status = getaddrinfo("www.google.lk", NULL, &hints, &res);
	if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status);
	else std::cout << "OK" << std::endl;
	WSACleanup();

	getchar(); getchar();

}