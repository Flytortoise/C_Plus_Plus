#include "Init.h"
#include "my_stock.h"
#include "Start.h"
#include "Date.h"
#include "Pass.h"
#include "Select_func.h"

void Init::init()
{
	Client_Stock * Client_Stock::client = NULL;
	start * start::my_start_ = NULL;
	Online_data * Online_data::data = NULL;
	Pass * Pass::pass_ = NULL;
	Select *Select::select_ = NULL;
}