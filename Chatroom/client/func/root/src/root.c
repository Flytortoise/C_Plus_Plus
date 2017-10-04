/***********************************
*函数名：root
*功能：超级用户功能
*时间：2017年2月25日 15:04:22
************************************/

#include <stdio.h>

#include "Pass.h"

extern int fd[2];

int Remove(int client_sock)		//踢人
{
	Node user;

    printf("请输入对方昵称:");
	scanf("%s",user.name);
	write(client_sock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));
	if(user.sock == -1)
	{
	    printf("		无联系人!\n");
	}
	else
	{
	    printf("		移除成功!\n");
	}

	return 0;
}

int OffChat(int client_sock)		//禁言
{
	Node user;

    printf("请输入对方昵称:");
	scanf("%s",user.name);
	write(client_sock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));
	if(user.sock == -1)
	{
	    printf("		无联系人!\n");
	}
	else
	{
	    printf("		禁言成功!\n");
	}
	return 0;
}

int OnChat(int client_sock)		//解除禁言
{
	Node user;

    printf("请输入对方昵称:");
	scanf("%s",user.name);
	write(client_sock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));
	if(user.sock == -1)
	{
	    printf("		无联系人!\n");
	}
	else
	{
	    printf("		解除禁言成功!\n");
	}

	return 0;
}
