#include "Change_Name.h"
#include "Data.h"
#include "Start.h"
#include "main.h"

int Callback2(void *para, int count, char **c_value, char **c_name)
{
    if(count != 0)
	{
	    return 1;
	}
	return 0;
}

int Change_Name::Function(int client_sock)
{
	sqlite3* db;
	char *etc = "etc/data.db";
	char *msg;
    char passwd[PASS_SIZE];
	char name[ACC_SIZE];
	char buffer[BUFF_SIZE];
	Node user;
	user.action = 1;

	memset(name,0,sizeof(name));
	memset(passwd,0,sizeof(passwd));
	memset(buffer,0,sizeof(buffer));

	vector<Node>::iterator t = OnlinePeople.begin();
	while(t != OnlinePeople.end())
	{
		if(t->sock == client_sock)
		{
			strcpy(name,t->name);	//获取当前用户的用户名		
		}
		t++;
	}

	read(client_sock,&user,sizeof(user));
	sqlite3_open(etc,&db);
	sprintf(buffer,"select * from user where password = '%s' AND name = '%s'",user.password,name);
	user.flag = sqlite3_exec(db,buffer,Callback2,NULL,&msg);	//查找用户名和密码是否匹配
	write(client_sock,&user,sizeof(user));
	strcpy(passwd,user.password);
	if(user.flag == 0)		//不匹配
	{
		sqlite3_close(db);
	    return 0;
	}	
	else		//匹配
	{
	    read(client_sock,&user,sizeof(user));		//读取新的用户名
		t = OnlinePeople.begin();
		while(t != OnlinePeople.end())
		{
			if(t->sock == client_sock)
			{
				strcpy(t->name,user.name);		//更改链表中的用户名
			}
			t++;
		}
		
		sprintf(buffer,"update user set name = '%s' where password = '%s' AND name = '%s'",user.name,user.password,name);
		user.flag = sqlite3_exec(db,buffer,NULL,NULL,&msg);		//更改数据库中的用户名
		write(client_sock,&user,sizeof(user));
		sqlite3_close(db);
		return 0;
	}
}

Change_Name * Change_Name::Change_Name_ = NULL;

Change_Name * Change_Name::GetChange_Name()
{
	if(Change_Name_ == NULL)
	{
		Change_Name_ = new Change_Name();
	}

	return Change_Name_;
}
void Change_Name::FreeChange_Name()
{
	if(Change_Name_ != NULL)
	{
		delete Change_Name_;
		Change_Name_ = NULL;
	}
}


Change_Name::Change_Name()
{

}

