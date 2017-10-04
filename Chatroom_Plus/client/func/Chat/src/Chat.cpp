#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "Chat.h"
#include "Start.h"

Chat * Chat::chat_ = NULL;

Chat * Chat::GetChat()
{
	if(chat_ == NULL)
	{
		chat_ = new Chat();
	}

	return chat_;
}
void Chat::FreeChat()
{
	if(chat_ != NULL)
	{
		delete chat_;
		chat_ = NULL;
	}
}


Chat::Chat()
{
	scan = MyScanf::GetScanf();
}

int Chat::Function(int client_stock)
{
    char etc[BUFF_SIZE];
	char *msg;
	time_t timep;
	char *time_save;
	char buffer[BUFF_SIZE];
	char name[ACC_SIZE];
	sqlite3 *db;
	
	memset(etc,0,sizeof(etc));
	sprintf(etc,"etc/_%s.db",id);

	Node user;
	read(fd[0],&user,sizeof(user));		//获取读写标志位
	if(user.chat_flag == 0)
	{
	    printf("		您已被禁言!\n");
		return 0;
	}

    printf("请输入对方昵称:");
	scanf("%s",user.name);
	getchar();
	strcpy(name,user.name);
	write(client_stock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));
	if(user.sock == -1)		//未在线
	{
	    printf("该联系人未在线，是否发送离线消息？\n");
		printf("1.是		2.否\n");
		scanf("%d",&user.off_line);
		getchar();
		if(user.off_line == 1)
		{
	    	printf("需要发送离线的消息:");
			scan->me_scanf(user.buffer);
			user.action = 0;
			write(client_stock,&user,sizeof(user));

			//保存到聊天记录中
			time(&timep);
			time_save = ctime(&timep);
			memset(buffer,0,sizeof(buffer));
			sqlite3_open(etc,&db);
			sprintf(buffer,"create table _%s(time text, name text, buffer text, flag text)",id);
			sqlite3_exec(db,buffer,NULL,NULL,&msg);
			memset(buffer,0,sizeof(buffer));
			sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','5')",id, time_save,name,user.buffer);
			sqlite3_exec(db,buffer,NULL,NULL,&msg);
			sqlite3_close(db);

			return 0;
			
		}
		else
		{
			write(client_stock,&user,sizeof(user));
			return 0;
		}
	}
	else
	{
	    printf("需要发送的消息:");
		scan->me_scanf(user.buffer);
		user.action = 0;
		write(client_stock,&user,sizeof(user));

		time(&timep);
		time_save = ctime(&timep);
		memset(buffer,0,sizeof(buffer));
		sqlite3_open(etc,&db);
		sprintf(buffer,"create table _%s(time text, name text, buffer text, flag text)",id);
		sqlite3_exec(db,buffer,NULL,NULL,&msg);
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','1')",id, time_save,name,user.buffer);
		sqlite3_exec(db,buffer,NULL,NULL,&msg);
		sqlite3_close(db);

		return 0;
	}
}

int Chat::Function() {}
