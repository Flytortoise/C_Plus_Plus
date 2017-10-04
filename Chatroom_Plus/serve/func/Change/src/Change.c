/***********************************
*函数名：Change
*功能：更改用户名或密码
*时间：2017年2月25日 14:51:20
************************************/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "Pass.h"

extern pNode head;

int Callback2(void *para, int count, char **c_value, char **c_name)
{
    if(count != 0)
	{
	    return 1;
	}
	return 0;
}

int Change_name(int client_sock)		//更改用户名
{
	sqlite3* db;
	char *etc = "etc/data.db";
	char *msg;
    char passwd[PASS_SIZE];
	char name[ACC_SIZE];
	char buffer[BUFF_SIZE];
	Node user;
	user.action = 1;

	memset(name,0,sizeof(name));
	memset(passwd,0,sizeof(passwd));
	memset(buffer,0,sizeof(buffer));

	pNode temp = head->next;
	while(temp != NULL)
	{
	    if(temp->sock == client_sock)
		{
		    strcpy(name,temp->name);	//获取当前用户的用户名
		}
	    temp = temp->next;
	}

	read(client_sock,&user,sizeof(user));
	sqlite3_open(etc,&db);
	sprintf(buffer,"select * from user where password = '%s' AND name = '%s'",user.password,name);
	user.flag = sqlite3_exec(db,buffer,Callback2,NULL,&msg);	//查找用户名和密码是否匹配
	write(client_sock,&user,sizeof(user));
	strcpy(passwd,user.password);
	if(user.flag == 0)		//不匹配
	{
		sqlite3_close(db);
	    return 0;
	}	
	else		//匹配
	{
	    read(client_sock,&user,sizeof(user));		//读取新的用户名
		temp = head->next;
		while(temp != NULL)
		{
	   		if(temp->sock == client_sock)
			{
			    strcpy(temp->name,user.name);		//更改链表中的用户名
			}
		    temp = temp->next;
		}
		sprintf(buffer,"update user set name = '%s' where password = '%s' AND name = '%s'",user.name,user.password,name);
		user.flag = sqlite3_exec(db,buffer,NULL,NULL,&msg);		//更改数据库中的用户名
		write(client_sock,&user,sizeof(user));
		sqlite3_close(db);
		return 0;
	}
}

int Change_passwd(int client_sock)		//更改密码
{
	Node user;
	sqlite3* db;
	char *etc = "etc/data.db";
	char *msg;
    char passwd[PASS_SIZE];
	char name[ACC_SIZE];
	char buffer[BUFF_SIZE];

	user.action = 1;
	memset(name,0,sizeof(name));
	memset(passwd,0,sizeof(passwd));
	memset(buffer,0,sizeof(buffer));

	pNode temp = head->next;
	while(temp != NULL)
	{
	    if(temp->sock == client_sock)
		{
		    strcpy(name,temp->name);		//当前用户的用户名
		}
	    temp = temp->next;
	}

	read(client_sock,&user,sizeof(user));
	sqlite3_open(etc,&db);
	sprintf(buffer,"select * from user where password = '%s' AND name = '%s'",user.password,name);
	user.flag = sqlite3_exec(db,buffer,Callback2,NULL,&msg);	//查找用户名，密码是否匹配
	write(client_sock,&user,sizeof(user));
	strcpy(passwd,user.password);
	if(user.flag == 0)		//不匹配
	{
		sqlite3_close(db);
	    return 0;
	}
	else		//匹配
	{
	    read(client_sock,&user,sizeof(user));
		sprintf(buffer,"update user set password = '%s' where password = '%s' AND name = '%s'",user.password,passwd,name);
		user.flag = sqlite3_exec(db,buffer,NULL,NULL,&msg);		//跟新密码
		write(client_sock,&user,sizeof(user));
		sqlite3_close(db);
		return 0;
	}
	

}
