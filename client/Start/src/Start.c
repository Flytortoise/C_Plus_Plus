/***********************************
*函数名：Start
*功能：入口函数
*时间：2017年2月25日 13:41:01
************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include "Pass.h"
#include "Select_func.h"

int fd[2];		//线程通信管道
int move = 1;	//是否被踢出标志位，被踢出时为0
int kong = 1;
char id[ID_SIZE];
pthread_t pid;	

void *Son(void *p)		//读线程
{
	char etc[BUFF_SIZE];
	char buffer[BUFF_SIZE];
	char *msg;
	time_t timep;
	char *time_save;
	sqlite3 *db;
	int client_sock = *((int *)p);
	int n_read;
	Node user;

	char ch;
	int i = 0;
	FILE *fp;

	while(1)
	{
		n_read = read(client_sock,&user,sizeof(user));		//循环从服务器读取数据
		memset(etc,0,sizeof(etc));
		sprintf(etc,"etc/_%s.db",id);
		if(n_read == 0)
		{
			printf("\n		服务器已关闭!\n");
			exit(-1);
		}

		switch(user.action)
		{
			case -6:
				printf("\n		%s对你发送文件 \n",user.name);
				sprintf(user.buffer,"%s_",user.buffer);
				fp = fopen(user.buffer,"w+");
				while((ch = user.send[i]) != '\0')
				{
					fputc(ch,fp);
				    i++;
				}
				i = 0;
				fclose(fp);
				break;
			case -5:		//离线信息
				//将离线消息加入到聊天记录的数据库
				time(&timep);
				time_save = ctime(&timep);
				memset(buffer,0,sizeof(buffer));
				sqlite3_open(etc,&db);
				sprintf(buffer,"create table _%s(time text, name text,buffer text,flag text)",id);
				sqlite3_exec(db,buffer,NULL,NULL,&msg);
				memset(buffer,0,sizeof(buffer));
				sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','6')",id,time_save,user.name,user.buffer);
				sqlite3_exec(db,buffer,NULL,NULL,&msg);
				sqlite3_close(db);
				printf("\n		%s对您发送的离线消息:%s\n",user.name,user.buffer);
				
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
				time(&timep);
				time_save = ctime(&timep);
				memset(buffer,0,sizeof(buffer));
				sqlite3_open(etc,&db);
				sprintf(buffer,"create table _%s(time text, name text,buffer text,flag text)",id);
				sqlite3_exec(db,buffer,NULL,NULL,&msg);
				memset(buffer,0,sizeof(buffer));
				sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','4')",id,time_save,user.name,user.buffer);
				sqlite3_exec(db,buffer,NULL,NULL,&msg);
				sqlite3_close(db);
				
				printf("\n		%s对大家说:%s\n",user.name,user.buffer);
				break;

			case 0:		//聊天信息
				kong = 0;
				//将私聊消息加入到聊天记录的数据库
				time(&timep);
				time_save = ctime(&timep);
				memset(buffer,0,sizeof(buffer));
				sqlite3_open(etc,&db);
				sprintf(buffer,"create table _%s(time text, name text,buffer text,flag text)",id);
				sqlite3_exec(db,buffer,NULL,NULL,&msg);
				memset(buffer,0,sizeof(buffer));
				sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','3')",id,time_save,user.name,user.buffer);
				sqlite3_exec(db,buffer,NULL,NULL,&msg);
				sqlite3_close(db);

				printf("\n		%s悄悄对你说:%s \n",user.name,user.buffer);
				break;

			default :	//默认信息
				write(fd[1],&user,sizeof(user));	//操作信息，直接发送给父线程
				break;
		}
	}
	close(fd[1]);
	return 0;
}

int Start(int p)
{
    int p_flag;
    int flag = SUCCESS;
    int client_sock = p;
	int one = 0;
	Node pass;	//登录后的返回值
	Node user;	//当前用户的具体信息

	p_flag = 0;
	pipe(fd);
	pthread_create(&pid,NULL,Son,(void *)&client_sock);		//创建读线程

	while(1)
	{	
		pass = Pass(client_sock);	//进行密码登录操作，登录成功则返回登录用户的信息
		strcpy(id,pass.id);

		if(pass.action != SUCCESS)	//用户退出登录
		{
		    break;
		}

    	
		one++;	
		move = 1;
		if(strcmp(pass.name,"root") == 0)		//判断是否为超级用户
		{
			while(flag == SUCCESS)
			{
				read(fd[0],&user,sizeof(user));		//读取当前用户的具体信息

				if(one == 1)
				{
					one--;
					interface_main2(user.name);		//打印一次功能界面
				}

				p_flag = Select_func2(client_sock,&flag,user.name);		//执行具体功能
				
				if(move == 0)		//判断是否被踢出
				{
				    user.flag = 0;
				}
				else
				{
				    user.flag = 1;
				}
				write(client_sock,&user,sizeof(user));
				
				if(p_flag == -1 || move == 0)
				{
				    break;
				}
			}
		}
		else		//普通用户
		{
			while(flag == SUCCESS)
			{
				read(fd[0],&user,sizeof(user));
				strcpy(id,user.id);

				if(one == 1)
				{
					one--;
					interface_main(user.name);		//打印一次功能选择界面
				}

				p_flag = Select_func(client_sock,&flag,user.name);	//执行具体功能

				if(move == 0)		//判断是否被管理员踢出
				{
				    user.flag = 0;
				}
				else
				{
				    user.flag = 1;
				}
				write(client_sock,&user,sizeof(user));	//将是否被踢出信息，发送给服务器

				if(p_flag == -1 || move == 0)	//被踢出或执行退出登录
				{
				    break;		//返回到用户登录界面
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
