//客户端链接
#ifndef MY_STOCK_H
#define MY_STOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>


//#include <string>	//c++好像把perror,exit,bzero都封装在里面
class Client_Sock
{
public :
    static Client_Sock* GetSock();
    static void FreeSock();
	int Action();

private :
    int client_sock;

	struct sockaddr_in client_addr;
	struct sockaddr_in serve_addr;

	static const int PORT = 8000;	//端口号

    static Client_Sock * client;
    static std::mutex client_lock;
    Client_Sock ();
};

#endif
