/*VER: https://cboard.cprogramming.com/c-programming/131008-udp-broadcast-client-server.html
LADO client!!


LINUX: Increase receiver socket or fill fail!!
sudo sysctl -w net.core.rmem_max=2304000
*/
#ifdef __linux__ 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define _BIND bind
#define _TCP_ID "10.130.20.187"  //linux
#define _CLOSE close
int Sleep(int sleepMs) { return usleep(sleepMs * 1000); }

#else
#include <winsock2.h>
#define snprintf _snprintf
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)
#define _BIND ::bind
#define _TCP_ID "10.121.18.193"   //internal:"127.0.0.1" net A:  10.121.18.193  net B:10:130:20:187
#define _CLOSE closesocket
#include <Windows.h> //Sleep
#endif


#include <iostream>

#define BUFLEN 62000  //Max length of buffer <65507
#define PORT_S 2450   //The port at server side

int main(void)
{
	struct sockaddr_in server;
	int sock, slen = sizeof(server);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;
	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
	//create socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_S);
	server.sin_addr.S_un.S_addr = inet_addr(_TCP_ID);

	//start communication
	while (1)
	{
		printf("Enter message : "); gets(message);
		//send the message
		if (sendto(sock, message, strlen(message), 0, (struct sockaddr *) &server, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		memset(buf, '\0', BUFLEN);//clear the buffer with previous data 
		//try to receive some data, this is a blocking call
		if (recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &server, &slen) == SOCKET_ERROR)
		{
			printf("\nrecvfrom() failed with error code : %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("Coming back message from the server: %s\n", buf);
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}