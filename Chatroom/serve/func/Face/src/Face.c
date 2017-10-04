/***********************************
*函数名：Face
*功能：发送表情
*时间：2017年2月25日 14:49:16
*备注：与私聊功能相似，不再备注
************************************/

#include <stdio.h>
#include <string.h>

#include "Pass.h"

extern pNode head;

int Face(int client_sock)
{
	Node user;
	char name[ACC_SIZE];
	pNode temp = head->next;
	user.sock = -1;
	user.action = 1;
	while(temp != NULL)
	{
	    if(temp->sock == client_sock)
		{
		    user.chat_flag = temp->chat_flag;
		}
		temp = temp->next;
	}
	write(client_sock,&user,sizeof(user));

	if(user.chat_flag == 0)
	{
	    return 0;
	}
	else
	{
		read(client_sock,&user,sizeof(user));
		temp = head->next;
		while(temp != NULL)
		{
	 	   if(strcmp(user.name,temp->name) == 0)
			{
			    user.sock = temp->sock;
			}

			if(client_sock == temp->sock)
			{
			    strcpy(name,temp->name);
			}

	   		temp = temp->next;
		}
		strcpy(user.name,name);
		write(client_sock,&user,sizeof(Node));

		if(user.sock == -1)
		{
	 	   return 0;
		}	
		else
		{
	  		read(client_sock,&user,sizeof(user));
			write(user.sock,&user,sizeof(user));
			return 0;
		}
	}

}
