#include "Look.h"
#include "Data.h"
#include "Start.h"
#include "main.h"

int Look::Function(int client_stock)
{
	Node user;
	vector<Node>::iterator t = OnlinePeople.begin();
	while(t != OnlinePeople.end())
	{
		user = *t;
		write(client_stock,&user,sizeof(Node));	//循环发送在线用户信息
		t++;
	}

	user.action = 1;
	user.sock = -1;
	write(client_stock,&user,sizeof(Node));		//发送结束标志

	return 0;
}

Look * Look::look_ = NULL;

Look * Look::GetLook()
{
	if(look_ == NULL)
	{
		look_ = new Look();
	}

	return look_;
}
void Look::FreeLook()
{
	if(look_ != NULL)
	{
		delete look_;
		look_ = NULL;
	}
}


Look::Look()
{

}

