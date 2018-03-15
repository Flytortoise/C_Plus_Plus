#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "Remove.h"
#include "Start.h"

Remove * Remove::Remove_ = NULL;

Remove * Remove::GetRemove()
{
	if(Remove_ == NULL)
	{
		Remove_ = new Remove();
	}

	return Remove_;
}
void Remove::FreeRemove()
{
	if(Remove_ != NULL)
	{
		delete Remove_;
		Remove_ = NULL;
	}
}


Remove::Remove()
{
	scan = MyScanf::GetScanf();
}

int Remove::Function(int client_sock)
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

int Remove::Function() {}
