#include "OffChat.h"
#include "Data.h"
#include "Start.h"
#include "main.h"


int OffChat::Function(int client_sock)
{
	Node user;

	read(client_sock,&user,sizeof(user));
	user.sock = -1;
	user.action = 1;
	vector<Node>::iterator t = OnlinePeople.begin();
	while(t != OnlinePeople.end())
	{
		if(strcmp(user.name,t->name) == 0)
		{
			user.sock = t->sock;
			t->chat_flag = 0;		//改变读写标志位
		}
		t++;
	}
	
	write(client_sock,&user,sizeof(Node));

	if(user.sock == -1)
	{
	    return 0;
	}
	else
	{
		user.action = -3;
		write(user.sock,&user,sizeof(user));		
		return 0;
	}
}

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

}

