#include <iostream>
#include "my_stock.h"
#include "Start.h"

using namespace std;

Serve_Stock * Serve_Stock::serve = NULL;

int main(int argc, char *argv[])
{
	pthread_t client_tidp;
	int client_stock;
	Serve_Stock * my_serve = Serve_Stock::GetStock();
	while(1)
	{
		client_stock = my_serve->Creat_stock();
		cout << "client_stock = " << client_stock << endl; 
		if(pthread_create(&client_tidp,NULL,Start,static_cast<void *>(&client_stock)) != 0)	//创建线程，单独为客户端工作
		{
		    perror("Pthread_create error!");
			exit(-1);
		}
	
	}
	 

	Serve_Stock::FreeStock();
	return 0;
}
