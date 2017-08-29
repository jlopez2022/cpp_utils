#include "Protocol_UDP_V003.hpp"

void fill_messages()
{ 
	for (int i = 0; i < UDP1_BUFFER_LONG; i++)
	{ 
		message1_long[i] = rand() % 256; message2_long[i] = rand() % 256; 
		if (i < 100) 
		{ 
			message1_short[i] = rand() % 256; message2_short[i] = rand() % 256; 
		} 
	} 
	message1_long[0] =  1;//message1 long
	message2_long[0] =  2;//message2 long
	message1_short[0] = 3;//message1 short
	message2_short[0] = 4;//message2 short

	message1_long[1] = 1;//RUN
	message2_long[1] = 1;//RUN
	message1_short[1] = 1;//RUN
	message2_short[1] = 1;//RUN
}


//================================== SERVER =================================
c_server::c_server()
{
	init_server();
}

void c_server::init_server()
{
	flag_end_server = false;
	state123 = 1;//RUN
	printf("initializing server\n");
	sockaddr_in server; //used in this function only to initiate socket
	memset((uchar*)&server, 0, sizeof(server));
#ifdef __linux__ 
	/*Fill in server's sockaddr_in*/
#define SOCKADDR struct sockaddr   
#else
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cout << "c_server::init_server()  WSAStartup() error" << endl; getchar();
		return;
	}
#endif

	/*Fill in server's sockaddr_in*/
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;//inet_addr(tcp_id);
	server.sin_port = htons(PORT_NUM);

	memset((char *)&anyclient, 0, sizeof(anyclient));
	anyclient.sin_family = AF_INET;
	anyclient.sin_addr.s_addr = INADDR_ANY;
	anyclient.sin_port = htons(0000);//any client port!
	int slen = sizeof(anyclient);

	/*Create socket */
	server_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_socket == -1)
	{
		cout << "Error in c_server::init_server(): socket failed"; getchar();
		return;
	}
	//bind(server_socket, (SOCKADDR*)&server_address, sizeof(SOCKADDR));
	if (_BIND(server_socket, (SOCKADDR *)&server, sizeof(server)) == -1)
	{
		cout<<"Fail bind()"; getchar();
		_CLOSE(server_socket); return;
	}
	int buffsize = 24 * UDP1_BUFFER_LONG;
	//Increasing the socket buffer:
	if (setsockopt(server_socket, SOL_SOCKET, SO_RCVBUF, (char*)&buffsize, sizeof(int)) == -1)
	{
		cout << "Warning at c_server::init_server() could not increase receiver socket size" << endl; getchar();
	}
	else
		cout << "Increased server socket bufer size" << endl;

	//the select side!
	//fd_set select_fd_set;//to be initiated!
	//struct timeval select_timeval;
	select_timeval.tv_sec = 0;
	select_timeval.tv_usec = TIMEOUT_US;
	FD_ZERO(&select_fd_set0);
	FD_SET(server_socket, &select_fd_set0);

	//BLOCKING/NON BLOCKING:
#ifdef NONBLOCKING
#ifdef __linux__
	int opt = 1; ioctl(server_socket, FIONBIO, &opt);
#else
	unsigned long opt; ioctlsocket(server_socket, FIONBIO, &opt);
#endif
#endif

}

void c_server::send_block(char *data_block, int size)
{
	int stat;
	stat = sendto(server_socket, data_block, size, 0, (struct sockaddr *) &anyclient, sizeof(anyclient)); //sends to any client!!
	if (stat == -1)
	{
		char line[256] = "### c_server::send_block failed:"; strcat(line, strerror(errno));
		cout_mtx.lock(); cout << line << endl; cout_mtx.unlock();
	}
}
int c_server::receive_block(char *data_block)
{
	si_length = sizeof(anyclient);
	int stat1 = -1;

	fd_set tmp = select_fd_set0;
	int ret = select((int)server_socket + 1, &tmp, NULL, NULL, &select_timeval);    
	switch (ret)
	{
	case 0: return 0;
	case -1: cout_mtx.lock(); cout << "WARNING AT c_server::receive_block() making select()" << endl; cout_mtx.unlock(); return -1;
	default: 
		stat1 = (int) recvfrom(server_socket, data_block, UDP1_BUFFER_LONG, 0, (struct sockaddr *) &anyclient, &si_length);
	}
	return stat1;//if -1 no data in!
}

bool c_server::flag_end_server;

void c_server::server_run_state()
{
	uchar message[UDP1_BUFFER_LONG];
	ushort *num_cmd = (ushort *)&message[2];
	uchar *cmd = &message[1];
	int num_cmd_sent = 0, num_cmd_in = 0, num_cmd_err = 0;

	while (!flag_end_server)
	{
		int i1 = receive_block((char *)message);
		if (i1 > 0)
		{
			num_cmd_in++;
			cout_mtx.lock();
			cout << "server in cmd:" << (int) message[0] << " cmd_num=" << *num_cmd << endl;
			cout_mtx.unlock();

			//send any cmd:
			if (*num_cmd == 10) state123 = 2;
			else if (*num_cmd == 20) state123 = 3;
			else if (*num_cmd == 30) state123 = 1;

			ushort num_cmd1 = *num_cmd;
			if (num_cmd1 % 2 == 0)
				memcpy(message, message1_short, 100);
			else
				memcpy(message, message2_short, 100);
			*num_cmd = num_cmd1;
			*cmd = state123;
			send_block((char *)message, 100); 
			num_cmd_sent++;
			cout_mtx.lock();
			cout << "server out cmd:" << (int) message[0] << " cmd_num=" << *num_cmd << endl;
			if ((i1 != 100) && (i1 != UDP1_BUFFER_LONG))
			{
				cout << "====== ERROR sercer received command length=" << i1 << endl;
				num_cmd_err++;
			}
			cout_mtx.unlock();
		}
	}
	cout_mtx.lock();
	cout << "===== END c_server::server_run_state() =====" << endl;
	cout << "Server sent commands=" << num_cmd_sent << " received=" << num_cmd_in << " wrong commands=" << num_cmd_err << endl;
	cout_mtx.unlock();
}

//====================================== c_client =========================================================
void c_client::init_client(const char *tcp_id)
{
	fill_messages();//initializes messages to be sent for testing
	//initiating socket:
#ifdef __linux__
	//client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("client socket() failed"); getchar();
		exit(EXIT_FAILURE);
	}
#else
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cout << "c_udp::init_client() WSAStartup() error" << endl; getchar();
		return;
	}

	//create socket
	if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("client socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
#endif
	/*Create client socket*/
	if (client_socket == -1)
	{
		cout << "Warning: client socket not created trying again:" << endl; int i1 = 1;
		if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&i1, sizeof(int)) < 0)
			perror("setsockopt(SO_REUSEADDR) failed");
	}

	/*Fill in client's sockaddr_in */
	memset(&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT_NUM);
	si_other.sin_addr.s_addr = inet_addr(tcp_id); // |= htonl(0x1ff);

	select_timeval.tv_sec = 0;
	select_timeval.tv_usec = 1;//1us
	FD_ZERO(&select_fd_set0);
	FD_SET(client_socket, &select_fd_set0);
	cout << "Connected c_client with server network ip: " << tcp_id << " Port=" << PORT_NUM << endl;

#ifdef NONBLOCKING
#ifdef __linux__
	int opt = 1;ioctl(client_socket, FIONBIO, &opt);
#else
	unsigned long opt; ioctlsocket(client_socket, FIONBIO, &opt);
#endif
#endif
}




void c_client::send_block(char *data_block, int size)
{
	int stat;
	stat = sendto(client_socket, data_block, size, 0, (struct sockaddr *) &si_other, sizeof(si_other)); //sends to server!!
	if (stat == -1)
	{
		char line[256] = "### c_client::send_block failed:"; strcat(line, strerror(errno)); 
		cout_mtx.lock(); cout << line << endl; cout_mtx.unlock();
	}
}
int c_client::receive_block(char *data_block)
{
	si_length = sizeof(si_other);
	int stat1 = -1;

	fd_set tmp = select_fd_set0;
	int ret = select((int)client_socket + 1, &tmp, NULL, NULL, &select_timeval);
	switch (ret)
	{
	case 0: return 0;
	case -1: cout_mtx.lock(); cout << "WARNING AT c_client::receive_block() making select()" << endl; cout_mtx.unlock(); return -1;
	default: 
		stat1 = (int) recvfrom(client_socket, data_block, UDP1_BUFFER_LONG, 0, (struct sockaddr *) &si_other, &si_length);
	}
	return stat1;//if -1 no data in!
}


void c_client::client_run_state()
{
	uchar message[UDP1_BUFFER_LONG];
	ushort *num_cmd = (ushort *)&message[2];
	int num_cmd_sent = 0, num_cmd_in = 0, num_cmd_err = 0;

	for (ushort i = 0; i < CMD_SENT; i++)
	{
		if (i % 8 == 0)
		{
			if ((i / 8) % 2 == 1)
				memcpy(message, message1_long, UDP1_BUFFER_LONG);
			else
				memcpy(message, message2_long, UDP1_BUFFER_LONG);
			*num_cmd = i;
			send_block((char *)message, UDP1_BUFFER_LONG);
			num_cmd_sent++;
			sleep_us(10000);
		}
		else
		{
			if (i % 2 == 1)
				memcpy(message, message1_short, 100);
			else
				memcpy(message, message2_short, 100);
			*num_cmd = i;
			send_block((char *)message, 100);
			num_cmd_sent++;
			sleep_us(2000);
		}
		cout_mtx.lock();
		cout << "client out cmd:" << (int) message[0] << " cmd_num=" << *num_cmd << endl;
		cout_mtx.unlock();

		int i1 = receive_block((char *)message);
		if (i1 > 0)
		{
			num_cmd_in++;
			cout_mtx.lock();
			cout << "client in cmd:" << (int)message[0] << " cmd_num=" << *num_cmd << endl;
			if ((i1 != 100) && (i1 != UDP1_BUFFER_LONG))
			{
				cout << "====== ERROR c_client received command length=" << i1 << endl;
				num_cmd_err++;
			}
			cout_mtx.unlock();
		}
	}
	cout_mtx.lock();
	cout << "===== END c_client::server_run_state() =====" << endl;
	cout << "Client sent commands=" << num_cmd_sent << " received=" << num_cmd_in << " wrong commands=" << num_cmd_err << endl;
	cout_mtx.unlock();
}


int main()
{
	c_client *client = new c_client(TCPID_SERVER);
	c_server *server = new c_server();
	//sending the server thread!!!
	cout << "Running threads" << endl;
	time_t ini, fin;

	ini = clock();
	thread th_server(&c_server::server_run_state, server);
	sleep_us(10000);
	thread th_client(&c_client::client_run_state, client);
	th_client.join();
	sleep_us(2000);//2ms
	server->set_end_state(true);
	th_server.join();
	fin = clock();
	cout << "\n============= END =============" << endl;
	cout << "Total time=" << 1.0*(fin - ini) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Expected>=" << CMD_SENT / 8 * 10e-3 + (CMD_SENT - CMD_SENT / 8)*2e-3 << " seconds" << endl;
	getchar();
	return 1;
}