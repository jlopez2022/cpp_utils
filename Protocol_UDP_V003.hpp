#ifndef  __PROTOCOLO_HPP
#define  __PROTOCOLO_HPP

/*
Version V000: Bien 2000 paquetes ok. Tarda lo mismo con TIMEOUT_US=1-500us si bien tarda 20-28s en mandar los 2000 paquetes debiendo ser algo mas de 6 segundos
V001: No select():
	  non-blocking     los 2000 paquetes son OK pero va lento: 84 segundos en vez de 28 con select().
	  En modo blocking los 2000 paquetes son OK (en init_server y init _client unsigned long mode=0) pero tarda 106 segundos
V002: Con select y non-blocking: va bien pero tarda un 15% mas que en modo blocking
V003: Se puede seleccionar entre blocking/nonblocking en linux y windows
      Modo blocking: tarda 16 segundos en mandar los 2000 paquetes (en modos release y debug x64)
	  Modo nonblocking: Tarda 18 segundos pero pierde el servidor 8 de 2000 paquetes

CAUTION: Increase receiver socket in Linux that is 8k long only!!!!!!!!!!!!!!!!!  :

    sudo sysctl -w net.core.rmem_max=2304000

	Compilation linux:

	gcc  -std=c++11 -lstdc++ -pthread -o protocol_exe protocol_VXXX.cpp protocol_VXXX.hpp
*/


#include <iostream> //cout
#include <stdio.h>  //getchar()
#include <stdlib.h> //srand
#include <string.h> //memcpy
#include <thread>   //threads, usleep
#include <chrono>	//usleep
#include <mutex>          // std::mutex

#ifdef __linux__ 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>    //usleep()
#define _BIND bind
#define TCPID_SERVER "10.130.20.187"  //linux. TCP_ID of the client. Used at the c_serverclass at send() and recvfrom()    MODIFY THIS!!!!!!!!!!!!!!!!!!!!!
#define _CLOSE close


#else
#include <winsock2.h>
#define snprintf _snprintf
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)     //to allow using linux standard compatible functions
#define _BIND ::bind
//internal:"127.0.0.1" net A:  10.121.18.193  net B:10:130:20:187
#define TCPID_SERVER "10.121.18.193"   //TCP_ID of the server. Used at the c_client class   MODIFY THIS!!!!!!!!!!!!!!!!!!!!!
#define _CLOSE closesocket
#endif

using namespace std;
typedef unsigned char uchar;
typedef unsigned short ushort;

//=========================== The UDP zone =================================================================
#define BLOCK_HEADER 0xBEADFEAC   //ADA1DEAD
#define UDP1_BUFFER_LONG 62000  //max UDP=65507. (1280*720+10)/15=61440.66 usamos 61441 y asi se aprovecha mejor
#define PORT_NUM   2450			//PORT for listening data, used by both
#define TIMEOUT_US 100			//TIMEOUT to be used in select()
#define CMD_SENT 2000			//Max number of c_client commands to be sent for testing purposes
//#define NONBLOCKING				//undef for making blocking. It is 15% slower in nonblocking!!!!!!!!!!!

void sleep_us(long microseconds){ this_thread::sleep_for(std::chrono::microseconds(microseconds)); }

uchar message1_long[UDP1_BUFFER_LONG], message2_long[UDP1_BUFFER_LONG];
uchar message1_short[100], message2_short[100];
void fill_messages();
std::mutex cout_mtx;

class c_server
{
public:
	c_server(); //no tcp_id needed at the server side!
	~c_server();
	void server_run_state(); //main function. pixels4=number of pixels (that are divided by 4 before being sent)
	void set_end_state(bool state){ flag_end_server = state; }//if false makes server_run_state() to exit!!
private:
	//socket variables:
#ifdef __linux__ 
	socklen_t si_length;
	int server_socket;//server side
	int clientToServer_socket; //client side
#else
	int si_length;
	SOCKET server_socket; //server side
	//SOCKET clientToServer_socket; //client side
#endif
	struct sockaddr_in  anyclient;
	//the select side!
	fd_set select_fd_set0;//select_fd_set0 is initiated once again server socket, then select_fd_set=select_fd_set0 every time select() is called
	struct timeval select_timeval;

	//private functions:
	void init_server();
	void send_block(char *data_block, int size);
	int receive_block(char *data_block);

	uchar state123;
	static bool flag_end_server;
};


class c_client
{
public:
	c_client(const char *tcp_id){ init_client(tcp_id); }
	~c_client() { }
	void client_run_state();
private:
	void init_client(const char *tcp_id);
	void send_block(char *data_block, int size);
	int receive_block(char *data_block);
	
	
	//private data to be used in sockets:
	struct sockaddr_in si_other;//this is the sockaddr_in needed at the client side to send to server
	//struct sockaddr_in si_client;//this is the sockaddr_in used to receivefrom server
#ifdef __linux__ 
	socklen_t si_length;
	int client_socket; //client side
#else
	int si_length;
	SOCKET client_socket; //Connected to server tcpid & port. Used at recvfrom() and sendto()
#endif
	//the select side!
	fd_set select_fd_set0;//to be initiated!
	struct timeval select_timeval;
};




#endif