
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Pass.h"
#include "Start.h"
#include "interface.h"		//登录界面
#include "my_scanf.h"		//密码保护


using namespace std;
extern int fd[2];		//线程通信管道

Pass * Pass::pass_ = NULL;

Pass::Pass()
{
	pass = Online_data::GetData();
	interface = Interface::GetInterface();
	my_scanf = MyScanf::GetScanf();	
}

Pass * Pass::GetPass()
{
	if(pass_ == NULL)
	{
		pass_ = new Pass();		
	}

	return pass_;
}

void Pass::FreePass()
{
	if(pass_ != NULL)
	{
		delete pass_;
		pass_ = NULL;
	}
}

int Pass::Action(){}

int Pass::Action(int client_sock)
{
	int i = 1;

	//printf("Pass1\n");
	while(1)
	{	
		if(i == 1)
		{
			system("clear");
    		interface->Action_pass();	//打印一次用户登录界面
			i--;
		}

		printf("请输入要执行的操作:");
		scanf("%d",&pass->action);
		if(pass->action == 1)		//登录操作
		{
		    printf("帐号:");
			scanf("%s",pass->id);
			printf("密码:");
			my_scanf->Action(pass->password,PASS_SIZE);		//输入保护密码
			write(client_sock,pass,sizeof(*pass));	//发送给服务器进行处理
		}
		else
		{
		    if(pass->action == 2)	//注册操作
			{
	   		 	printf("用户名:");
				scanf("%s",pass->name);
				printf("密码:");
				scanf("%s",pass->password);		//注册不进行密码保护
				write(client_sock,pass,sizeof(*pass));
			}
			else		//退出操作
			{
			    write(client_sock,pass,sizeof(*pass));
				return 0;		//退出直接返回
			}
		}
	
		read(fd[0],pass,sizeof(*pass));		//读取服务器处理后的结果
		system("clear");
		interface->Action_pass();
		switch(pass->action)
		{
		    case 1:
		    {
				printf("登录成功!\n");
				return 1;
			}break;
	
			case 2:
			{
				printf("密码错误!\n");
			}break;
	
			case 3:
			{
				printf("帐号未注册!\n");
			}break;
	
			case 4:
			{
				printf("帐号已存在!\n");
			}break;
	
			case 5:
			{
				printf("注册成功!\n");
				printf("您的帐号为:%s\n",pass->id);
			}break;

			case 6:
			{
			    printf("已在线，请勿重复登录!\n");
			}break;
		}
	}	
}

