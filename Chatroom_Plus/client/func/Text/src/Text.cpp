#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "Text.h"
#include "Start.h"

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
	scan = MyScanf::GetScanf();
}

int Text::Function(int client_sock)
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
	write(client_sock,&user,sizeof(user));
	read(fd[0],&user,sizeof(user));
	if(user.sock == -1)		//未在线
	{
		printf("对方未在线！\n");
		return 0;
			
	}
	else
	{
		memset(user.buffer,0,sizeof(user.buffer));
	    printf("需要发送的文件:");
		scan->me_scanf(user.buffer);
		user.action = -6;
		
		FILE *fp = fopen(user.buffer,"r+");
		if(fp == NULL)
		{
		    printf("无该文件！\n");
			user.send_flag = 0;
			write(client_sock,&user,sizeof(user));
			fclose(fp);
		}
		else
		{
			char ch;
			int i = 0;
			memset(user.send,0,sizeof(user.send));
			while((ch = fgetc(fp)) != EOF)
			{
			    user.send[i++] = ch;
				if(i == SEND_SIZE)
				{
					printf("文件太大发送失败！\n");
					break;
				}
			}

			if(ch == EOF)
			{
			    user.send_flag = 1;
				printf("发送成功！\n");
			}
			else
			{
			    user.send_flag = 0;
			}

			write(client_sock,&user,sizeof(user));
			fclose(fp);
		}

		return 0;
	}	//打印一次功能选择界面
}

int Text::Function() {}
