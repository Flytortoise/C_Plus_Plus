#include "my_stock.h"
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int Client_Stock::Action(int t){}
Client_Stock * Client_Stock::client = NULL;
Client_Stock :: Client_Stock()
{
	client_stock = socket(AF_INET,SOCK_STREAM,0);	//创建客户端的套接字
	if(client_stock < 0)
	{
	    perror("Client_sock error!");
		exit(-1);
	}

	bzero(&serve_addr,sizeof(serve_addr));
	serve_addr.sin_family = AF_INET;
	serve_addr.sin_port = htons(PORT);
	serve_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

int Client_Stock :: Action()
{
	if(connect(client_stock,(struct sockaddr *)&serve_addr,sizeof(struct sockaddr_in)) < 0)		//链接服务器
    {
	    perror("Connect error!");
		exit(-1);
	}

	return client_stock;
}

Client_Stock* Client_Stock::GetStock()
{
	if(client == NULL)
	{
		client = new Client_Stock();
	}
	
	return client;
}

void Client_Stock::FreeStock()
{
	if(client != NULL)
	{
		printf("%d Client over !\n",client->client_stock);
		delete client;
		client = NULL;
	}
}
