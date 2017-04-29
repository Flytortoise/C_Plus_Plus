#include <iostream>
#include "my_stock.h"

using namespace std;

void* Start(void *p)
{
	cout << "Start" << endl;	
}

Serve_Stock * Serve_Stock::serve = NULL;

int main(int argc, char *argv[])
{
	pthread_t client_tidp;
	Serve_Stock * my_serve = Serve_Stock::GetStock();
	int client_stock = my_serve->Creat_stock();
	cout << "client_stock = " << client_stock << endl; 
	if(pthread_create(&client_tidp,NULL,Start,(void *)client_stock) != 0)	//创建线程，单独为客户端工作
	{
	    perror("Pthread_create error!");
		exit(-1);
	}
	

	Serve_Stock::FreeStock();
	return 0;
}
