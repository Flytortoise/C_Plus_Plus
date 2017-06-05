#include "AllChat.h"
#include "Data.h"
#include "Start.h"
#include "main.h"

int AllChat::Function(int client_sock)
{
	Node user;
	vector<Node>::iterator t = OnlinePeople.begin();
	user.action = 1;
	while(t != OnlinePeople.end())
	{
		if(t->sock == client_sock)
		{
			user.chat_flag = t->chat_flag;			
		}
		t++;
	}
	write(client_sock,&user,sizeof(user));		//将当前用户的读写标志位发送个客户端

	if(user.chat_flag == 0)		//被禁言，直接返回
	{
	    return 0;
	}
	else
	{
		read(client_sock,&user,sizeof(user));	//读取客户端发送的信息
		t = OnlinePeople.begin();
		while(t != OnlinePeople.end())
		{
			if(t->sock == client_sock)
			{
				strcpy(user.name,t->name);		//读取发送方的姓名		
			}
			t++;
		}

		t = OnlinePeople.begin();
		while(t != OnlinePeople.end())
		{
			write(t->sock,&user,sizeof(user));		//将信息发送给每一个在线用户
			t++;
		}

	}
	return 0;
}

AllChat * AllChat::AllChat_ = NULL;

AllChat * AllChat::GetAllChat()
{
	if(AllChat_ == NULL)
	{
		AllChat_ = new AllChat();
	}

	return AllChat_;
}
void AllChat::FreeAllChat()
{
	if(AllChat_ != NULL)
	{
		delete AllChat_;
		AllChat_ = NULL;
	}
}


AllChat::AllChat()
{

}

