#include "Remove.h"
#include "Data.h"
#include "Start.h"
#include "main.h"


int Remove::Function(int client_sock)
{
	Node user;
	read(client_sock,&user,sizeof(user));
	user.sock = -1;
	user.action = 1;
	vector<Node>::iterator t = OnlinePeople.begin();
	while(t != OnlinePeople.end())
	{
	    if(strcmp(user.name,t->name) == 0)		//查询该用户是否在线
		{
		    user.sock = t->sock;
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
		t = OnlinePeople.begin();
		while(t != OnlinePeople.end())		//从在线用户链表移除
		{
			if(strcmp(t->name,user.name) == 0)
			{
			    t = OnlinePeople.erase(t);	
			}
			else
			{
			    t++;
			}
		}

		user.action = -2;
		write(user.sock,&user,sizeof(user));
		return 0;
	}
}

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

}

