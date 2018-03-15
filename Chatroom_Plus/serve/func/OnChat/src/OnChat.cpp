#include "OnChat.h"
#include "Data.h"
#include "Start.h"
#include "main.h"


int OnChat::Function(int client_sock)
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
			t->chat_flag = 1;
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
	    user.action = -4;
		write(user.sock,&user,sizeof(user));
		return 0;
	}
}

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

}

