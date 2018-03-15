#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

#include "Select_func.h"
#include "Data.h"

#include "DynBase.h"
#include "Look.h"
#include "Chat.h"
#include "Exit.h"

using namespace std;

int Select_Direct::Direct(int t, int *) {}
int Select_Direct::Direct2(int t, int *) {}
Select* Select::select_ = NULL;

Select::Select()
{
	Func = NULL;
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
	Node user;
	read(client_sock,&user,sizeof(user));		//获取具体操作
	Fact = reinterpret_cast<AB_Factory *>(DynObjectFactory::CreateObject(user.Sel));
	Func = Fact->Factory();
	return Func->Function(client_sock);
}


//超级用户功能
int Select::Direct2(int client_sock,int *flag)
{
	Node user;
	read(client_sock,&user,sizeof(user));
	switch(user.action)
	{
	    case 1:
		{
		    Func = Look::GetLook();
		    Func->Function(client_sock);		//查看当前用户
		}break;

	    case 2:
		{
		    //Chat(client_sock);
		}break;

	    case 3:
		{
		    //All_Chat(client_sock);
		}break;
	    
		case 4:
		{
		    //Fast(client_sock);
		}break;

	    case 5:
		{
		    //Face(client_sock);
		}break;

	    case 6:
		{
		    //Change_name(client_sock);
		}break;

	    case 7:
		{
		    //Change_passwd(client_sock);
		}break;

	    case 8:
		{
		    
		}break;

	    case 9:
		{
			//File(client_sock);
		}break;

	    case 10:
		{
		    //return Exit_Log(client_sock);
		}break;

	    case 11:
		{
		    //Exit(client_sock,flag);
		}break;

		case 12:
		{

		}break;

	    case 13:
		{
		    //Remove(client_sock);		//踢出用户
		}break;

	    case 14:
		{
		   // OffChat(client_sock);		//禁言
		}break;

	    case 15:
		{
		    //OnChat(client_sock);		//解除禁言
		}break;

		default :
		{
		}break;
	}

	return 0;
}

int Select::Direct(int t)
{

}
