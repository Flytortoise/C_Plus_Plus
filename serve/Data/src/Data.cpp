#include "Data.h"
#include <stdio.h>
using namespace std;

Online_data::Online_data()
{

}

Online_data::~Online_data()
{
	
}

Online_data* Online_data::GetData()
{
	if(data == NULL)
	{
		data = new Online_data();		
	}

	return data;
}

void Online_data::FreeData()
{
	if(data != NULL)
	{
		delete data;
		data = NULL;
	}
}

