/***********************************
*函数名：Look
*功能：查看在线用户
*时间：2017年2月25日 14:59:24
************************************/

#include <stdio.h>

#include "Pass.h"

extern pNode head;
int Look(int client_sock)
{
	Node flag;
	pNode temp = head->next;
	Node user;
	while(temp != NULL)
	{
	    write(client_sock,temp,sizeof(Node));	//循环发送在线用户信息
		temp = temp->next;
	}

	user.action = 1;
	user.sock = -1;
	write(client_sock,&user,sizeof(Node));		//发送结束标志
}
