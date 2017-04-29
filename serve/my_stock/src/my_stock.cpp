#include "my_stock.h"
#include <errno.h>
#include <arpa/inet.h>

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
	serve_addr.sin_addr.s_addr = inet_addr("192.168.1.189");	//在arpa头文件中

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

int Serve_Stock :: Creat_stock()
{
	bzero(&client_addr,sizeof(client_addr));
	if((client_stock = accept(serve_stock,(struct sockaddr *)&client_addr,&sockaddr_len)) < 0)
	{
	    perror("Accept error !");
		exit(-1);
	}			//接收客户端

	return client_stock;
}
