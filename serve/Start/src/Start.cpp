#include "Start.h"
#include <strings.h>
#include <string.h>
#include <iostream>

using namespace std;

start::start()
{
	char *etc2 = "etc/temp.db";
	user = Online_data::GetData();
	pass = Pass::GetPass();
	select = Select_func::GetSelect();
}

AB_Director * start::CreateStart()
{
	if(my_start_ == NULL )
	{
		my_start_ = new start;		
	}

	return my_start_;
}

void start::FreeStart()
{
	if(my_start_ != NULL)
	{
		delete my_start_;
		my_start_ = NULL;
	}
}

int start::OffLine(void *para, int count, char **c_value, char **c_name)	
{
    int client_sock = *((int *)para);
	Node user;
	bzero(&user,sizeof(user));
	strcpy(user.name,c_value[0]);
	strcpy(user.buffer,c_value[1]);
	user.action = -5;
	write(client_sock,&user,sizeof(user));		//存在离线消息，则发送给该用户
	return 0;
}

void start::Date_base()	//数据库处理
{
	char buffer[BUFF_SIZE];
	sqlite3_open(etc2,&db2);
	sprintf(buffer,"select * from _%s",user->name);
	sqlite3_exec(db2,buffer,OffLine,(void *)&client_sock,&msg);
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"drop table _%s",user->name);
	sqlite3_exec(db2,buffer,NULL,NULL,&msg);	//处理完毕后，销毁离线消息
	sqlite3_close(db2);

}

int start::Direct(int client_stock)
{
	int flag = 1;		//重复执行功能
	int p_flag;		//退出登录的标志位
	Node tmp;		//tmp保存是否被踢出功能的标志位
	tmp.action = 1;

	while(1)
	{
		user = pass->Action(client_sock);
		if(user.action == -1)		//退出操作
		{
		    break;
		}
		user->sock = client_sock;
		user->action = 1;
		user->chat_flag = 1;
		OnlinePeople.push_back(*user);
		Date_base();


		while(flag == 1)		//具体功能入口
		{
			write(client_sock,user,sizeof(Node));	//将当前用户信息发送个客户端
			if(strcmp(user->name,"root") == 0)		//判断是否为超级用户
			{
				p_flag = select->Select_func2(client_sock,&flag);	//执行具体功能
				read(client_sock,&tmp,sizeof(Node));	//tmp保存是否被踢出功能的标志位
				if(p_flag == -1 || tmp.flag == 0)		//执行退出登录或者被管理员提出，则回到用户登录
				{
				    break;
				}
			}
			else
			{
				p_flag = select->Select_func(client_sock,&flag);	//执行具体功能
				read(client_sock,&tmp,sizeof(Node));	//tmp保存是否被踢出功能的标志位
				if(p_flag == -1 || tmp.flag == 0)		//执行退出登录或者被管理员提出，则回到用户登录
				{
				    break;
				}
			}
    	}

		if(flag == 0)		//执行退出聊天室功能，则退出
		{
		    break;
		}
	}

	return 0;
}

