/***********************************
*函数名：Exit_Log
*功能：退出登录
*时间：2017年2月25日 14:57:01
************************************/

#include <stdio.h>

#include "Pass.h"
extern pNode head;
int Exit_Log(int client_sock)
{	
	pNode die;
	pNode temp = head;		//从在线链表删除该用户
	while(temp->next != NULL)
	{
	    die = temp->next;
	    if(die->sock == client_sock)
		{
			temp->next = die->next;
			free(die);
		}
		else
		{
			temp = temp->next;
		}
	}

	return -1;
}
