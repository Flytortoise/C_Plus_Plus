#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "Abstract.h"
#include "my_stock.h"
#include "Start.h"


using namespace std;

void * Start (void *p);


//Client_Stock::client = NULL;
vector <Online_data> OnlinePeople;
int main(int argc, char *argv[])
{
	pthread_t client_tidp;
	int client_stock;
	

	AB_Action * my_serve = Serve_Stock::GetStock();
	while(1)
	{
		client_stock = my_serve->Action();
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

void * Start (void *p)
{
	start *my_start = new start();
	my_start->Direct(*(static_cast<int *>(p)));
	delete my_start;
}
