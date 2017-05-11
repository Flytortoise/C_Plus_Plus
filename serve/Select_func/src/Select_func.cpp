

#include <stdio.h>
#include <signal.h>
#include "Select_func.h"
#include "Data.h"


int Select_Direct::Direct(int t, int *) {}
int Select_Direct::Direct2(int t, int *) {}


Select::Select()
{

}

Select * Select::GetSelect()
{
	if(select_ == NULL)
	{
		select_ = new Select();
	}
	return select_;
}

void Select::FreeSelect()
{
	if(select_ != NULL)
	{
		delete select_;
		select_ = NULL;
	}
}

int Select::Direct(int client_sock,int *flag)
{
	printf("Direct\n");
}


//超级用户功能
int Select::Direct2(int client_sock,int *flag)
{
	printf("Direct2\n");
}

int Select::Direct(int t)
{

}
