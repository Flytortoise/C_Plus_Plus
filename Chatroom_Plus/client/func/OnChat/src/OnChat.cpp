#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "OnChat.h"
#include "Start.h"

OnChat * OnChat::OnChat_ = NULL;

OnChat * OnChat::GetOnChat()
{
	if(OnChat_ == NULL)
	{
		OnChat_ = new OnChat();
	}

	return OnChat_;
}
void OnChat::FreeOnChat()
{
	if(OnChat_ != NULL)
	{
		delete OnChat_;
		OnChat_ = NULL;
	}
}


OnChat::OnChat()
{
	scan = MyScanf::GetScanf();
}

int OnChat::Function(int client_sock)
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

int OnChat::Function() {}
