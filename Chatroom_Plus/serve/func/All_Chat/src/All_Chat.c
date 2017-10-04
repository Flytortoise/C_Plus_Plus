/***********************************
*函数名：All_Chat
*功能：群聊
*时间：2017年2月25日 14:38:43
************************************/

#include <stdio.h>
#include <string.h>

#include "Pass.h"

extern pNode head;

int All_Chat(int client_sock)
{
	Node user;
	pNode temp = head->next;
	user.action = 1;
	while(temp != NULL)
	{
	    if(temp->sock == client_sock)
		{
			user.chat_flag = temp->chat_flag;
		}
		temp = temp->next;
	}
	write(client_sock,&user,sizeof(user));		//将当前用户的读写标志位发送个客户端

	if(user.chat_flag == 0)		//被禁言，直接返回
	{
	    return 0;
	}
	else
	{
		read(client_sock,&user,sizeof(user));	//读取客户端发送的信息
		temp = head->next;
		while(temp != NULL)
		{
			if(client_sock == temp->sock)
			{
			    strcpy(user.name,temp->name);		//读取发送方的姓名
			}

	 	   temp = temp->next;
		}

		temp = head->next;
		while(temp != NULL)
		{

			write(temp->sock,&user,sizeof(user));		//将信息发送给每一个在线用户
		    temp = temp->next;
		}
	}
	return 0;

}
