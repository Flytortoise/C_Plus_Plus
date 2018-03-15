#include "Start.h"
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

char id[ID_SIZE];
int fd[2];		//线程通信管道
int move = 1;	//是否被踢出标志位，被踢出时为0
int kong = 1;
pthread_t pid;

sqlite3 * start::db;
start * start::my_start_ = NULL;
start::start()
{
	user = Online_data::GetData();
	pass = Pass::GetPass();
	select = Select::GetSelect();
	interface = Interface::GetInterface();
}

start * start::CreateStart()
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

void Data_base(int action, Node & users)	//数据库操作
{
	time_t timep;
	char *time_save;
	char etc[BUFF_SIZE];
	char buffer[BUFF_SIZE];
	char *msg;

	time(&timep);
	time_save = ctime(&timep);
	memset(buffer,0,sizeof(buffer));
	sqlite3_open(etc,&start::db);
	sprintf(buffer,"create table _%s(time text, name text,buffer text,flag text)",id);
	sqlite3_exec(start::db,buffer,NULL,NULL,&msg);
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','%d')",id,time_save,users.name,users.buffer,action);
	sqlite3_exec(start::db,buffer,NULL,NULL,&msg);
	sqlite3_close(start::db);
}

void SendText(Node &users)	//发送文件
{
	char buffer[BUFF_SIZE];

	int i = 0;
	char ch;
	sprintf(users.buffer,"%s_",users.buffer);
	FILE *fp = fopen(users.buffer,"w+");
	while((ch = users.send[i]) != '\0')
	{
		fputc(ch,fp);
	    i++;
	}
	fclose(fp);
}


void * Son(void *p)	//读线程
{
	char etc[BUFF_SIZE];
	char buffer[BUFF_SIZE];

	char *msg;

	int client_stock = *((int *)p);
	int n_read;
	Node users;

	while(1)
	{
		n_read = read(client_stock,&users,sizeof(users));		//循环从服务器读取数据
		memset(etc,0,sizeof(etc));
		sprintf(etc,"etc/_%s.db",id);
		if(n_read == 0)
		{
			printf("\n		服务器已关闭!\n");
			exit(-1);
		}

		switch(users.action)
		{
			case -6:
				printf("\n 		%s对你发送文件 \n",users.name);
				SendText(users);

				break;
			case -5:		//离线信息
				//将离线消息加入到聊天记录的数据库
				Data_base(6,users);
				printf("\n		%s对您发送的离线消息:%s\n",users.name,users.buffer);
				
				break;
			case -4:		
				printf("\n		管理员已解除您的禁言！\n");
				break;

			case -3:		
				printf("\n		管理员已将您禁言!\n");
				break;

			case -2:
				printf("\n		您已被管理员移出!\n");
				move = 0;
				break;

			case -1:		//群聊信息
				//将群聊消息加入到聊天记录的数据库
				Data_base(4,users);
				
				printf("\n		%s对大家说:%s\n",users.name,users.buffer);
				break;

			case 0:		//聊天信息
				kong = 0;
				//将私聊消息加入到聊天记录的数据库
				Data_base(3,users);

				printf("\n		%s悄悄对你说:%s \n",users.name,users.buffer);
				break;

			default :	//默认信息
				write(fd[1],&users,sizeof(users));	//操作信息，直接发送给父线程
				break;
		}
	}
	close(fd[1]);
}


int start::Direct(int client_stock)
{
	char etc[BUFF_SIZE];
	char buffer[BUFF_SIZE];
	char *msg;
    int flag = 1;
	int one = 0;
	int p_flag;

	pipe(fd);

	pthread_create(&pid,NULL,Son,static_cast<void *>(&client_stock));		//创建读线程
	//printf("start1\n");
	while(1)
	{
		pass->Action(client_stock);	//进行密码登录操作，登录成功则返回登录用户的信息
		strcpy(id,user->id);
		if(user->action != 1)	//用户退出登录
		{
		    break;
		}

		one++;	
		move = 1;
		if(strcmp(user->id,"root") == 0)		//判断是否为超级用户
		{
			while(flag == 1)
			{
				read(fd[0],user,sizeof(Node));		//读取当前用户的具体信息

				if(one == 1)
				{
					one--;
					interface->Action2(user->name);		//打印一次功能界面
				}

				p_flag = select->Direct2(client_stock,&flag,user->name);		//执行具体功能
				
				if(move == 0)		//判断是否被踢出
				{
				    user->flag = 0;
				}
				else
				{
				    user->flag = 1;
				}
				write(client_stock,user,sizeof(Node));
				
				if(p_flag == -1 || move == 0)
				{
				    break;
				}

				if(p_flag == -2)
				{
					flag = 0;
					break;
				}
			}
		}
		else		//普通用户
		{
			while(flag == 1)
			{
				read(fd[0],user,sizeof(Node));
				if(one == 1)
				{
					one--;
					interface->Action(user->name);		//打印一次功能选择界面
				}
				
				p_flag = select->Direct(client_stock,&flag,user->name);	//执行具体功能

				if(move == 0)		//判断是否被管理员踢出
				{
				    user->flag = 0;
				}
				else
				{
				    user->flag = 1;
				}
				write(client_stock,user,sizeof(Node));	//将是否被踢出信息，发送给服务器
				if(p_flag == -1 || move == 0)	//被踢出或执行退出登录
				{
				    break;		//返回到用户登录界面
				}

				if(p_flag == -2)
				{
					flag = 0;
					break;
				}
			}
		}
		
		if(flag == 0)		//执行退出聊天室
		{	
			break;
		}
	}

	close(fd[0]);
	return 0;
}

int start::Direct()
{

}

