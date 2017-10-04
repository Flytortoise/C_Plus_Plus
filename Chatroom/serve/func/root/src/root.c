/***********************************
*函数名：root
*功能：超级用户功能
*时间：2017年2月25日 15:04:22
************************************/

#include <stdio.h>
#include <string.h>

#include "Pass.h"

extern pNode head;

int Remove(int client_sock)		//踢人
{
	Node user;
	pNode temp = head->next;
	pNode die;

	read(client_sock,&user,sizeof(user));
	user.sock = -1;
	user.action = 1;

	while(temp != NULL)
	{
	    if(strcmp(user.name,temp->name) == 0)		//查询该用户是否在线
		{
		    user.sock = temp->sock;
		}

	    temp = temp->next;
	}
	write(client_sock,&user,sizeof(Node));

	if(user.sock == -1)
	{
	    return 0;
	}
	else
	{
		temp = head;
		while(temp->next != NULL)		//从在线用户链表移除
		{
		    die = temp->next;
			if(strcmp(die->name,user.name) == 0)
			{
			    temp->next = die->next;
				free(die);
			}
			else
			{
			    temp = temp->next;
			}
		}

		user.action = -2;
		write(user.sock,&user,sizeof(user));
		return 0;
	}
}

int OffChat(int client_sock)		//禁言
{
	Node user;
	pNode temp = head->next;

	read(client_sock,&user,sizeof(user));
	user.sock = -1;
	user.action = 1;

	while(temp != NULL)
	{
	    if(strcmp(user.name,temp->name) == 0)		//查询是否在线
		{
		    user.sock = temp->sock;
			temp->chat_flag = 0;		//改变读写标志位
		}
	    temp = temp->next;
	}
	write(client_sock,&user,sizeof(Node));

	if(user.sock == -1)
	{
	    return 0;
	}
	else
	{
		user.action = -3;
		write(user.sock,&user,sizeof(user));		
		return 0;
	}
}

int OnChat(int client_sock)		//解除禁言
{
	Node user;
	pNode temp = head->next;

	read(client_sock,&user,sizeof(user));
	user.sock = -1;
	user.action = 1;

	while(temp != NULL)
	{
	    if(strcmp(user.name,temp->name) == 0)		//查询是否在线
		{
		    user.sock = temp->sock;
			temp->chat_flag = 1;		//改变读写标志位
		}

	    temp = temp->next;
	}
	write(client_sock,&user,sizeof(Node));

	if(user.sock == -1)
	{
	    return 0;
	}
	else
	{
	    user.action = -4;
		write(user.sock,&user,sizeof(user));
		return 0;
	}
}
