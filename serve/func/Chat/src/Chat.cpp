#include "Chat.h"
#include "Data.h"
#include "Start.h"

int Chat::Function(int client_sock)
{
	Node user;
	vector<Node>::iterator t = start::OnlinePeople.begin();
	char name[ACC_SIZE];
	user.sock = -1;		//初始化
	user.action = 1;

	char *msg;
	char *etc2 = "etc/temp.db";
	char buffer[BUFF_SIZE];
	char id[ID_SIZE];
	char name2[ACC_SIZE];
	sqlite3 *db2;

	while(t != start::OnlinePeople.end())
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

		t = start::OnlinePeople.begin();
		while(t != start::OnlinePeople.end())
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
			read(client_sock,&user,sizeof(user));
			if(user.off_line == 1)		//发送离线消息
			{
				//在服务器建立数据库保存离线消息
				sqlite3_open(etc2,&db2);
				sprintf(buffer,"create table _%s(name text,buffer text)",name2);
				sqlite3_exec(db2,buffer,NULL,NULL,&msg);
				memset(buffer,0,sizeof(buffer));
				sprintf(buffer,"insert into _%s(name,buffer) values ('%s','%s')",name2, name, user.buffer);
				sqlite3_exec(db2,buffer,NULL,NULL,&msg);
				sqlite3_close(db2);
		   		return 0;
			}
			else
			{
			    return 0;
			}
		}
		else
		{
		    read(client_sock,&user,sizeof(user));
			write(user.sock,&user,sizeof(user));		//发送信息
			return 0;
		}
	}
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

