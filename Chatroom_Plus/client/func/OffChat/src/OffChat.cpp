#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "OffChat.h"
#include "Start.h"

OffChat * OffChat::OffChat_ = NULL;

OffChat * OffChat::GetOffChat()
{
	if(OffChat_ == NULL)
	{
		OffChat_ = new OffChat();
	}

	return OffChat_;
}
void OffChat::FreeOffChat()
{
	if(OffChat_ != NULL)
	{
		delete OffChat_;
		OffChat_ = NULL;
	}
}


OffChat::OffChat()
{
	scan = MyScanf::GetScanf();
}

int OffChat::Function(int client_sock)
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

int OffChat::Function() {}
