#include "my_stock.h"
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

Serve_Stock* Serve_Stock::serve = NULL;
Serve_Stock :: Serve_Stock()
{
	sockaddr_len = sizeof(struct sockaddr);

	serve_stock = socket(AF_INET,SOCK_STREAM,0);
	if(serve_stock < 0)
	{
	    perror("Serve_sock error!");
		exit(-1);
	}

	on = 1;
	if(setsockopt(serve_stock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) < 0)
	{
	    perror("Setsockopt error !");
		exit(-1);
	}			//使服务器可以多次绑定

	bzero(&serve_addr,sizeof(serve_addr));
	serve_addr.sin_family = AF_INET;	
	serve_addr.sin_port = htons(PORT);	
	serve_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//在arpa头文件中

	if(bind(serve_stock,(struct sockaddr *)&serve_addr,sockaddr_len) < 0 )
	{
        perror("Bind error!");
		exit(-1);
	}			//绑定套接字

	if(listen(serve_stock,5) < 0)		//设置监听器
	{
	    perror("Listen error !");
		exit(-1);
	}
}

int Serve_Stock :: Action()
{
	bzero(&client_addr,sizeof(client_addr));
	if((client_stock = accept(serve_stock,(struct sockaddr *)&client_addr,&sockaddr_len)) < 0)
	{
	    perror("Accept error !");
		exit(-1);
	}			//接收客户端

	return client_stock;
}

int Serve_Stock ::  Action(int t)
{
	Action();
}

Serve_Stock* Serve_Stock::GetStock()
{
	if(serve == NULL)
	{
		serve = new Serve_Stock();
	}
	
	return serve;
}

void Serve_Stock::FreeStock()
{
	if(serve != NULL)
	{
		printf("Serve over !\n");
		delete serve;
		serve = NULL;
	}
}
