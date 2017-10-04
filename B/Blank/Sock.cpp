#include "Sock.h"
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <QMessageBox>
#include <mutex>
#include <QDebug>


Client_Sock * Client_Sock::client = NULL;
std::mutex Client_Sock::client_lock;

Client_Sock :: Client_Sock()
{
    client_sock = socket(AF_INET,SOCK_STREAM,0);	//创建客户端的套接字
    if(client_sock < 0)
	{
        perror("Client_Sock error!");
		exit(-1);
	}

	bzero(&serve_addr,sizeof(serve_addr));
	serve_addr.sin_family = AF_INET;
	serve_addr.sin_port = htons(PORT);
	serve_addr.sin_addr.s_addr = inet_addr("192.168.1.189");
}

int Client_Sock::Action()
{
    int ret;
   // qDebug()<< "???";
    while(connect(client_sock,(struct sockaddr *)&serve_addr,sizeof(struct sockaddr_in)) < 0)		//链接服务器
    {
        ret = QMessageBox::question(NULL,"Connect error!","Connect Again?",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
        if(ret == QMessageBox::No)
        {
            exit(-1);
        }
	}

    return client_sock;
}

Client_Sock* Client_Sock::GetSock()
{
    std::unique_lock<std::mutex> lock(client_lock);
	if(client == NULL)
	{
        client = new Client_Sock();
	}
	
	return client;
}

void Client_Sock::FreeSock()
{
    std::unique_lock<std::mutex> lock(client_lock);
	if(client != NULL)
	{
        printf("%d Client over !\n",client->client_sock);
		delete client;
		client = NULL;
	}
}
