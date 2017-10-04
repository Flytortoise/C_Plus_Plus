/***********************************
*函数名：Change
*功能：更改用户名或密码
*时间：2017年2月25日 14:51:20
************************************/

#include <stdio.h>

#include "Pass.h"
#include "my_scanf.h"
extern int fd[2];

int Change_name(int client_sock)		//更改用户名
{
	Node user;

    printf("请输入密码:");	
	my_scanf(user.password,PASS_SIZE);		//密码保护
	write(client_sock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));		//读取服务器发送的信息
	if(user.flag == 0)
	{
	    printf("		密码错误!\n");
		return 0;
	}
	else
	{
	    printf("请输入新的昵称:");
		scanf("%s",user.name);		//获取新昵称
		write(client_sock,&user,sizeof(user));
		read(fd[0],&user,sizeof(user));
		if(user.flag == 0)
		{
		    printf("		昵称已修改!!\n");
		}
		else
		{
		    printf("		修改失败....\n");
		}

		return 0;
	}

}

int Change_passwd(int client_sock)		//更改密码
{
    Node user;
    printf("请输入密码:");
	my_scanf(user.password,PASS_SIZE);		//密码保护
	write(client_sock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));		
	if(user.flag == 0)
	{
	    printf("		密码错误!\n");
		return 0;
	}
	else
	{
	    printf("请输入新的密码:");
		scanf("%s",user.password);		//修改密码
		write(client_sock,&user,sizeof(user));
		read(fd[0],&user,sizeof(user));
		if(user.flag == 0)
		{
		    printf("		密码已修改!!\n");
		}
		else
		{
		    printf("		修改失败....\n");
		}

		return 0;
	}

}
