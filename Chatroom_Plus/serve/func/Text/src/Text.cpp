#include "Text.h"
#include "Data.h"
#include "Start.h"
#include "main.h"


int Text::Function(int client_sock)
{
	Node user;
	char name[ACC_SIZE];
	
	user.sock = -1;		//初始化
	user.action = 1;

	char *msg;
	//char *etc2 = "etc/temp.db";
	char buffer[BUFF_SIZE];
	char id[ID_SIZE];
	char name2[ACC_SIZE];
	sqlite3 *db2;
	vector<Node>::iterator t = OnlinePeople.begin();
	while(t != OnlinePeople.end())
	{
		if(t->sock == client_sock)
		{
			user.chat_flag = t->chat_flag;			
		}
		t++;
	}
	
	write(client_sock,&user,sizeof(user));		//发送读写标志位
	if(user.chat_flag == 0)
	{
			return 0;	//已被禁言
	}
	else
	{
		read(client_sock,&user,sizeof(user));		

		t = OnlinePeople.begin();
		while(t != OnlinePeople.end())
		{
		    if(strcmp(user.name,t->name) == 0)
			{
			    user.sock = t->sock;		//获取接收方的套接字
			}

			if(client_sock == t->sock)
			{
			    strcpy(name,t->name);	//获取发送方的姓名
			}

		    t++;
		}
		strcpy(name2,user.name);
		strcpy(user.name,name);
		write(client_sock,&user,sizeof(Node));

		if(user.sock == -1)		//离线消息操作
		{
		
			return 0;
		}
		else
		{
		    read(client_sock,&user,sizeof(user));
			if(user.send_flag == 0)
			{
			    return 0;
			}

			write(user.sock,&user,sizeof(user));		//发送文件
			return 0;
		}
	}
}

Text * Text::Text_ = NULL;

Text * Text::GetText()
{
	if(Text_ == NULL)
	{
		Text_ = new Text();
	}

	return Text_;
}
void Text::FreeText()
{
	if(Text_ != NULL)
	{
		delete Text_;
		Text_ = NULL;
	}
}


Text::Text()
{

}

