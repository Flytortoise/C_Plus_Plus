/***********************************
*函数名：Look
*功能：查看在线用户
*时间：2017年2月25日 14:59:24
************************************/

#include <stdio.h>
#include <strings.h>

#include "Pass.h"

extern int fd[2];
int Look(int client_sock)
{
    Node temp;
	printf("当前在线用户:\n");
	while(1)		//循环接收在线用户信息
	{
	    bzero(&temp,sizeof(temp));
	    read(fd[0],&temp,sizeof(temp));
		if(temp.sock == -1)		//结束标志
		{
		    break;
		}
		else
		{
		    printf("		%s\n",temp.name);
		}
	}
}
