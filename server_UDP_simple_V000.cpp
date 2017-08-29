/*VER: https://cboard.cprogramming.com/c-programming/131008-udp-broadcast-client-server.html
LADO SERVER!!

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

#else
#include <winsock2.h>
#define snprintf _snprintf
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)
#define _BIND ::bind
#define _TCP_ID "10.121.18.193"   //internal:"127.0.0.1" net A:  10.121.18.193  net B:
#define _CLOSE closesocket
#endif

#include <iostream>

#define BUFLEN 62000  //Max length of buffer <65507
#define PORT_S 2450   //The port at server side
#define PORT_C 0000   //Any port of any client 

int main()
{
	SOCKET sock;
	int recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	printf("\nInitialising Winsock...");//Initialise winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT_S);

	struct sockaddr_in client;
	memset((char *)&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(PORT_C);
	int slen = sizeof(client);


	//Bind
	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
	while (1)//keep listening for data
	{
		printf("Waiting for data..."); fflush(stdout);

		memset(buf, '\0', BUFLEN);//clear the buffer with previous data by filling null
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &client, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		printf("Data: %s\n", buf);

		//now reply the client with the same data
		if (sendto(sock, buf, recv_len, 0, (struct sockaddr*) &client, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}

