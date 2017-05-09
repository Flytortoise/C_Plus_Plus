/***********************************
*函数名：Exit
*功能：退出聊天室
*时间：2017年2月25日 14:57:01
************************************/

#include <stdio.h>

#include "Pass.h"
extern pNode head;
int Exit(int client_sock,int *flag)
{
    *flag = 0;		//将标志位置为0
	pNode die;
	pNode temp = head;
	while(temp->next != NULL)		//从在线用户链表删除该用户
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
	return 0;
}
