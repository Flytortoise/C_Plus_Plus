#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "Start.h"
#include "Select_func.h"
#include "Data.h"

#include "Look.h"
#include "Chat.h"
#include "Exit.h"

#include "DynBase.h"
using namespace std;

extern int move;
Select *Select::select_ = NULL;
int Select_Direct::Direct(int t, int *, char *) {}
int Select_Direct::Direct2(int t, int *, char *) {}

int Select_Direct::Direct(){}
int Select_Direct::Direct(int t){}

Select::Select()
{
	Func = NULL;
}

Select * Select::GetSelect()
{
	if(select_ == NULL)
	{
		select_ = new Select;
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

int Select::Direct(int client_sock,int *flag,char *name)
{
	Node user;

aa:	printf("请输入要执行的操作:\n");
	cout << "look/chat/out"  << endl;
	cin >> user.Sel;
	if(move == 0)		//如果被踢出，改变标志位
	{
	    user.action = -1;
	}

	if(strcmp(user.Sel,"look")== 0 || strcmp(user.Sel,"chat")== 0 || strcmp(user.Sel,"out")== 0 )
	{
		write(client_sock,&user,sizeof(user));
		Fact = reinterpret_cast<AB_Factory *>(DynObjectFactory::CreateObject(user.Sel));
		Func = Fact->Factory();
		Func->Function(client_sock);	
	}
	else
	{

		cout << "请输入正确的指令！" << endl;	
		goto aa;	
	}	
/*
	switch(user.action)
	{
		case -1:
		{
		    return 0;		//被踢出直接返回
		}break;

	    case 1:
		{	
			Func = Look::GetLook();
		    Func->Function(client_sock);		//查看当前用户
		}break;

	    case 2:
		{
			Func = Chat::GetChat();
		    Func->Function(client_sock);		//私聊
		}break;

	    case 3:
		{
		   // All_Chat(client_sock);		//群聊
		}break;

	    case 4:
		{
		   // Fast(client_sock);		//发送快捷消息
		}break;

	    case 5:
		{
		   // Face(client_sock);		//发送表情
		}break;

	    case 6:
		{
		    //Change_name(client_sock);		//更改用户名
		}break;

	    case 7:
		{
		    //Change_passwd(client_sock);		//更改密码
		}break;

	    case 8:
		{
		    //interface_main(name);		//查看帮助
		}break;

	    case 9:
		{
			//File(client_sock);
		}break;

	    case 10:
		{
		   // return Exit_Log();		//退出登录
		}break;

	    case 11:
		{
			*flag = 0;	//退出聊天室
		}break;

		case 12:
		{
		   // Save();			//查看聊天记录
		}break;

		default :
		{
			printf("请输入正确的指令!!\n");
		}
	}
*/
	return 0;
}


//超级用户功能
int Select::Direct2(int client_sock,int *flag,char *name)
{
	Node user;

	printf("请输入要执行的操作:");
	scanf("%d",&user.action);
	write(client_sock,&user,sizeof(user));
	switch(user.action)
	{
	    case 1:
		{
		    //Look(client_sock);
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
		   // Fast(client_sock);
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
		    //interface_main2(name);
		}break;

	    case 9:
		{
			//File(client_sock);
		}break;

	    case 10:
		{
		    //return Exit_Log();
		}break;

	    case 11:
		{
		    //Exit(flag);
		}break;

		case 12:
		{
		   // Save();
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
		   // OnChat(client_sock);		//解除禁言
		}break;
		default :
		{
			printf("请输入正确的指令!!\n");
		}
	}

	return 0;
}
