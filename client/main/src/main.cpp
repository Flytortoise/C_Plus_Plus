#include <iostream>
#include "my_stock.h"

using namespace std;

void Start()
{
	cout << "Start"<< endl;	
}

int main(int argc, char *argv[])
{
	Client_Stock my_client;
	int client_stock = my_client.My_Connect();
	cout << "client_stock = " << client_stock << endl; 
	
	Start();

	return 0;
}
