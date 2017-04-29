//套接字类

#ifndef MY_STOCK_H
#define MY_STOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>	//c++好像把perror,exit,bzero都封装在里面
using namespace std;
class Client_Stock 
{
public :
	Client_Stock ();
	int My_Connect();
	
private :
	int client_stock;

	struct sockaddr_in client_addr;
	struct sockaddr_in serve_addr;

	static const int PORT = 8000;	//端口号
};

#endif
