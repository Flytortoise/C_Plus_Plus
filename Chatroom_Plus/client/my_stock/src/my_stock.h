//套接字类

#ifndef MY_STOCK_H
#define MY_STOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Abstract.h"
//#include <string>	//c++好像把perror,exit,bzero都封装在里面
class Client_Stock : public AB_Action
{
public :
	static Client_Stock* GetStock();
	static void FreeStock();
	int Action();
	int Action(int t);

	
private :
	int client_stock;

	struct sockaddr_in client_addr;
	struct sockaddr_in serve_addr;

	static const int PORT = 8000;	//端口号

	static Client_Stock * client;
	Client_Stock ();
};

#endif
