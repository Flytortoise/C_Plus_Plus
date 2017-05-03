//套接字类

#ifndef MY_STOCK_H
#define MY_STOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Abstract.h"
//#include <string>	//c++好像把perror,exit,bzero都封装在里面
class Serve_Stock : public AB_Action
{
public :
	int Action();
	static Serve_Stock* GetStock();
	static void FreeStock();

private :
	int on;
	int serve_stock;
	int client_stock;
	socklen_t sockaddr_len;
	struct sockaddr_in serve_addr;
	struct sockaddr_in client_addr;

	static const int PORT = 8000;	//端口号

	Serve_Stock();
	static Serve_Stock * serve;
};

#endif
