#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "Start.h"
#include "Select_func.h"
#include "Data.h"


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

int Select::Check(char *s)
{
	
	if(!strcmp(s,"look") || !strcmp(s,"chat") || !strcmp(s,"out") || !strcmp(s,"allchat") || !strcmp(s,"fast"))
	{
		return 1;
	}

	if(!strcmp(s,"face") || !strcmp(s,"changename")|| !strcmp(s,"changepasswd"))
	{
		return 1;
	}
	if(!strcmp(s,"help") || !strcmp(s,"text")|| !strcmp(s,"ex")|| !strcmp(s,"record"))
	{
		return 1;
	}

	return 0;
}

int Select::Check2(char *s)
{
	if(Check(s))
	{
		return 1;
	}
	else if(!strcmp(s,"onchat") || !strcmp(s,"offchat")|| !strcmp(s,"away"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Select::Direct(int client_sock,int *flag,char *name)
{
	Node user;

aa:	printf("请输入要执行的操作:\n");
	cout << "look/chat/allchat/fast/"  << endl;
	cout << "/face/changename/changepasswd/help" << endl;
	cout << "/text/ex/out/record" << endl;
	cin >> user.Sel;
	if(move == 0)		//如果被踢出，改变标志位
	{
	    user.action = -1;
	}

	if(Check(user.Sel))
	{
		write(client_sock,&user,sizeof(user));
		Fact = reinterpret_cast<AB_Factory *>(DynObjectFactory::CreateObject(user.Sel));
		Func = Fact->Factory();
		return Func->Function(client_sock);	
	}
	else
	{

		cout << "请输入正确的指令！" << endl;	
		goto aa;	
	}	

}


//超级用户功能
int Select::Direct2(int client_sock,int *flag,char *name)
{
	Node user;

bb:	printf("请输入要执行的操作:\n");
	cout << "look/chat/allchat/fast/"  << endl;
	cout << "/face/changename/changepasswd/help/" << endl;
	cout << "/text/ex/out/record/" << endl;
	cout << "/onchat/offchat/away" << endl;
	cin >> user.Sel;
	if(move == 0)		//如果被踢出，改变标志位
	{
	    user.action = -1;
	}

	if(Check2(user.Sel))
	{
		write(client_sock,&user,sizeof(user));
		Fact = reinterpret_cast<AB_Factory *>(DynObjectFactory::CreateObject(user.Sel));
		Func = Fact->Factory();
		return Func->Function(client_sock);	
	}
	else
	{

		cout << "请输入正确的指令！" << endl;	
		goto bb;	
	}	

}
