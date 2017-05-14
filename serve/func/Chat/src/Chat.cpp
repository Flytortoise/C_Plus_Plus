#include "Chat.h"
#include "Data.h"
#include "Start.h"

int Chat::Function(int client_stock)
{
	Node user;
	vector<Node>::iterator t = start::OnlinePeople.begin();
	while(t != start::OnlinePeople.end())
	{
		user = *t;
		write(client_stock,&user,sizeof(Node));	//循环发送在线用户信息
		t++;
	}

	user.action = 1;
	user.sock = -1;
	write(client_stock,&user,sizeof(Node));		//发送结束标志
}

Chat * Chat::Chat_ = NULL;

Chat * Chat::GetChat()
{
	if(Chat_ == NULL)
	{
		Chat_ = new Chat();
	}

	return Chat_;
}
void Chat::FreeChat()
{
	if(Chat_ != NULL)
	{
		delete Chat_;
		Chat_ = NULL;
	}
}


Chat::Chat()
{

}

