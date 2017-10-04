#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "Change_Name.h"
#include "Start.h"

Change_Name * Change_Name::Change_Name_ = NULL;

Change_Name * Change_Name::GetChange_Name()
{
	if(Change_Name_ == NULL)
	{
		Change_Name_ = new Change_Name();
	}

	return Change_Name_;
}
void Change_Name::FreeChange_Name()
{
	if(Change_Name_ != NULL)
	{
		delete Change_Name_;
		Change_Name_ = NULL;
	}
}


Change_Name::Change_Name()
{
	scan = MyScanf::GetScanf();
}

int Change_Name::Function(int client_sock)
{
    Node user;

    printf("请输入密码:");	
	scan->Action(user.password,PASS_SIZE);		//密码保护
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

int Change_Name::Function() {}
