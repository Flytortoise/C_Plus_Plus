#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "Change_Passwd.h"
#include "Start.h"

Change_Passwd * Change_Passwd::Change_Passwd_ = NULL;

Change_Passwd * Change_Passwd::GetChange_Passwd()
{
	if(Change_Passwd_ == NULL)
	{
		Change_Passwd_ = new Change_Passwd();
	}

	return Change_Passwd_;
}
void Change_Passwd::FreeChange_Passwd()
{
	if(Change_Passwd_ != NULL)
	{
		delete Change_Passwd_;
		Change_Passwd_ = NULL;
	}
}


Change_Passwd::Change_Passwd()
{
	scan = MyScanf::GetScanf();
}

int Change_Passwd::Function(int client_sock)
{
    Node user;
    printf("请输入密码:");
	scan->Action(user.password,PASS_SIZE);		//密码保护
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

int Change_Passwd::Function() {}
