

#include <stdio.h>
#include <signal.h>
#include "Select_func.h"
#include "Data.h"

Select::Select()
{

}

Select * GetSelect()
{
	if(Select_ == NULL)
	{
		Select_ = new Select;
	}
	return Select_;
}

void FreeSelect()
{
	if(Select_ != NULL)
	{
		delete Select_;
		Select_ = NULL;
	}
}

int Select::Action(int client_sock,int *flag,char *name)
{
	printf("Action\n");
}


//超级用户功能
int Select::Action2(int client_sock,int *flag,char *name)
{
	printf("Action2\n");
}
