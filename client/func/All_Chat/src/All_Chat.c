/***********************************
*函数名：All_Chat
*功能：群聊
*时间：2017年2月25日 14:38:43
************************************/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "Pass.h"

extern int fd[2];
extern char id[ID_SIZE];
int All_Chat(int client_sock)
{
	char etc[BUFF_SIZE];
	char *msg;
	time_t timep;
	char *time_save;
	char buffer[BUFF_SIZE];
	char name[ACC_SIZE] = "all";
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

	printf("需要发送的消息:");
	scanf("%s",user.buffer);
	user.action = -1;		//群发消息标志位
	write(client_sock,&user,sizeof(user));	


	//保存到聊天记录数据库中
	time(&timep);
	time_save = ctime(&timep);
	memset(buffer,0,sizeof(buffer));
	sqlite3_open(etc,&db);
	sprintf(buffer,"create table _%s(time text, name text, buffer text, flag text)",id);
	sqlite3_exec(db,buffer,NULL,NULL,&msg);
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"insert into _%s(time,name,buffer,flag) values ('%s','%s','%s','2')",id, time_save,name,user.buffer);
	sqlite3_exec(db,buffer,NULL,NULL,&msg);
	sqlite3_close(db);
	return 0;

}
