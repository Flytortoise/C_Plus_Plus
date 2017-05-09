/***********************************
*函数名：Save
*功能：查看聊天记录
*时间：2017年2月25日 15:02:06
************************************/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "Pass.h"

extern char id[ID_SIZE];

int Search(void *para, int count, char **c_value,char **c_name)
{
	printf("\n时间:%s",c_value[0]);
	if(strcmp(c_value[3],"1") == 0)
	{
		printf("您对%s发送信息:\n",c_value[1]);
		printf("%s\n",c_value[2]);
	}

	if(strcmp(c_value[3],"2") == 0)
	{
		printf("您对大家发送信息:\n");
		printf("%s\n",c_value[2]);

	}

	if(strcmp(c_value[3],"3") == 0)
	{
		printf("%s向您发送的私聊信息:\n",c_value[1]);
		printf("%s\n",c_value[2]);

	}

	if(strcmp(c_value[3],"4") == 0)
	{
		printf("%s向您发送的群发信息:\n",c_value[1]);
		printf("%s\n",c_value[2]);

	}

	if(strcmp(c_value[3],"5") == 0)
	{
		printf("您对%s发送的离线信息:\n",c_value[1]);
		printf("%s\n",c_value[2]);
	}

	if(strcmp(c_value[3],"6") == 0)
	{
		printf("%s向您发送的离线信息:\n",c_value[1]);
		printf("%s\n",c_value[2]);
	}

    return 0;
}

int Save()
{
	char etc[BUFF_SIZE];
	char *msg;
	sqlite3* db;
	char buffer[BUFF_SIZE];
	
	memset(etc,0,sizeof(etc));
	memset(buffer,0,sizeof(buffer));
	sprintf(etc,"etc/_%s.db",id);		//ID唯一，根据ID创建专属的聊天记录数据库

	sqlite3_open(etc,&db);
	sprintf(buffer,"select * from _%s",id);
	sqlite3_exec(db,buffer,Search,NULL,&msg);		//根据标志位打印不同的信息
	
	sqlite3_close(db);
    return 0;
}
