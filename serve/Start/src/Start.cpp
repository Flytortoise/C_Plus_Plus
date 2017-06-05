#include "Start.h"
#include <strings.h>
#include <string.h>
#include <iostream>
#include "main.h"

using namespace std;
start* start::my_start_ = NULL;
start::start()
{
	char *etc2 = "etc/temp.db";
	//user = Online_data::GetData();
	pass = Pass::GetPass();
	select = Select::GetSelect();
}

int start::flag = 0;

start * start::CreateStart()
{
	if(my_start_ == NULL )
	{
		my_start_ = new start();		
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

int OffLine(void *para, int count, char **c_value, char **c_name)	
{
    int client_sock = *((int *)para);
	Online_data * user = Online_data::GetData();
	bzero(user,sizeof(*user));
	strcpy(user->name,c_value[0]);
	strcpy(user->buffer,c_value[1]);
	user->action = -5;
	write(client_sock,user,sizeof(*user));		//存在离线消息，则发送给该用户
	return 0;
}

void start::Date_base(int client_stock)	//数据库处理
{
	char buffer[BUFF_SIZE];
	sqlite3_open(etc2_,&db2_);
	sprintf(buffer,"select * from _%s",user.name);
	sqlite3_exec(db2_,buffer,OffLine,(void *)&client_stock,&msg_);
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"drop table _%s",user.name);
	sqlite3_exec(db2_,buffer,NULL,NULL,&msg_);	//处理完毕后，销毁离线消息
	sqlite3_close(db2_);

}

int start::Direct(int client_stock)
{
	vector<Node>::iterator t;
	flag = 1;		//重复执行功能
	int p_flag;		//退出登录的标志位
	Node tmp;		//tmp保存是否被踢出功能的标志位
	tmp.action = 1;
	//printf("start1\n");
	while(1)
	{
		pass->Action(client_stock);
		if(user.action == -1)		//退出操作
		{
		    break;
		}
		printf("123\n");
		strcpy(user.name,(Online_data::GetData())->name);
		strcpy(user.id,(Online_data::GetData())->id);
		user.sock = client_stock;
		user.action = 1;
		user.chat_flag = 1;
		OnlinePeople.push_back(user);
		Date_base(client_stock);

		while(flag == 1)		//具体功能入口
		{	
			write(client_stock,&user,sizeof(Node));	//将当前用户信息发送个客户端
			if(strcmp(user.name,"root") == 0)		//判断是否为超级用户
			{
				p_flag = select->Direct2(client_stock,&flag);	//执行具体功能
				read(client_stock,&tmp,sizeof(Node));	//tmp保存是否被踢出功能的标志位
				if(p_flag == -1 || tmp.flag == 0)		//执行退出登录或者被管理员提出，则回到用户登录
				{
				    break;
				}
			}
			else
			{
				printf("ONname = %s\n",Online_data::GetData()->name);
				p_flag = select->Direct(client_stock,&flag);	//执行具体功能
				read(client_stock,&tmp,sizeof(Node));	//tmp保存是否被踢出功能的标志位
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

