#include <iostream>
#include "my_stock.h"
#include "Abstract.h"
#include "Start.h"
#include "Init.h"

using namespace std;

void Start(int);

Client_Stock * Client_Stock::client = NULL;
start * start::my_start_ = NULL;
Online_data * Online_data::data = NULL;
Pass * Pass::pass_ = NULL;
MyScanf *MyScanf::scanf_ = NULL;
Interface *Interface::interface_ = NULL;
Select *Select::select_ = NULL;

int main(int argc, char *argv[])
{
	Init::init();
	AB_Action *my_client = Client_Stock::GetStock();
	int client_stock = my_client->Action();
	cout << "client_stock = " << client_stock << endl; 
	Start(client_stock);
	Client_Stock::FreeStock();
	return 0;
}

void Start(int client_stock)
{
	AB_Director *my_start = start::CreateStart();
	my_start->Direct(client_stock);
	start::FreeStart();
}
