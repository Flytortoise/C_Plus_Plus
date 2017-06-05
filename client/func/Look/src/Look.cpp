#include "Look.h"
#include "Start.h"

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

int Look::Function(int client_stock)
{
    Node temp;
	printf("当前在线用户:\n");
	while(1)		//循环接收在线用户信息
	{
	    bzero(&temp,sizeof(temp));
	    read(fd[0],&temp,sizeof(temp));
		if(temp.sock == -1)		//结束标志
		{
		    break;
		}
		else
		{
		    printf("		%s\n",temp.name);
		}
	}
	
	return 0;
}

int Look::Function() {}
