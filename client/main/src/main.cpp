#include <iostream>
#include "my_stock.h"

using namespace std;

void Start()
{
	cout << "Start"<< endl;	
}
Client_Stock * Client_Stock::client = NULL;
int main(int argc, char *argv[])
{
	Client_Stock *my_client = Client_Stock::GetStock();
	int client_stock = my_client->My_Connect();
	cout << "client_stock = " << client_stock << endl; 
	
	Start();
	Client_Stock::FreeStock();
	return 0;
}
