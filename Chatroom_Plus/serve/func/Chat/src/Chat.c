/***********************************
*函数名：Chat
*功能：私聊
*时间：2017年2月25日 14:43:42
************************************/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "Pass.h"

extern pNode head;

int Chat(int client_sock)
{
	Node user;
	char name[ACC_SIZE];
	pNode temp = head->next;
	user.sock = -1;		//初始化
	user.action = 1;

	char *msg;
	char *etc2 = "etc/temp.db";
	char buffer[BUFF_SIZE];
	char id[ID_SIZE];
	char name2[ACC_SIZE];
	sqlite3 *db2;
	while(temp != NULL)
	{
	    if(temp->sock == client_sock)
		{
		    user.chat_flag = temp->chat_flag;
		}
		temp = temp->next;
	}
	write(client_sock,&user,sizeof(user));		//发送读写标志位
	if(user.chat_flag == 0)
	{
			return 0;	//已被禁言
	}
	else
	{
		read(client_sock,&user,sizeof(user));		

		temp = head->next;
		while(temp != NULL)
		{
		    if(strcmp(user.name,temp->name) == 0)
			{
			    user.sock = temp->sock;		//获取接收方的套接字
			}

			if(client_sock == temp->sock)
			{
			    strcpy(name,temp->name);	//获取发送方的姓名
			}

		    temp = temp->next;
		}
		strcpy(name2,user.name);
		strcpy(user.name,name);
		write(client_sock,&user,sizeof(Node));

		if(user.sock == -1)		//离线消息操作
		{
			read(client_sock,&user,sizeof(user));
			if(user.off_line == 1)		//发送离线消息
			{
				//在服务器建立数据库保存离线消息
				sqlite3_open(etc2,&db2);
				sprintf(buffer,"create table _%s(name text,buffer text)",name2);
				sqlite3_exec(db2,buffer,NULL,NULL,&msg);
				memset(buffer,0,sizeof(buffer));
				sprintf(buffer,"insert into _%s(name,buffer) values ('%s','%s')",name2, name, user.buffer);
				sqlite3_exec(db2,buffer,NULL,NULL,&msg);
				sqlite3_close(db2);
		   		return 0;
			}
			else
			{
			    return 0;
			}
		}
		else
		{
		    read(client_sock,&user,sizeof(user));
			write(user.sock,&user,sizeof(user));		//发送信息
			return 0;
		}
	}
}
