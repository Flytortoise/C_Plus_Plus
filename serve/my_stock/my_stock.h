#ifndef MY_STOCK_H
#define MY_STOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class AB_Stock
{
public :
	virtual int Creat_stock() = 0;
	virtual int Init();
};

class Serve_Stock
{
public :
	Serve_Stock();
	int Creat_stock();
	
private :
	int serve_stock;
	int client_stock;
	struct sockaddr_in serve_addr;
	struct sockaddr_in client_addr;

	static const SERVE_IP = "192.168.1.189";	//服务器IP
	static const PORT = 8000;	//端口号
};

#endif