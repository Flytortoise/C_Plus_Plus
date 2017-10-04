#include "Change_Passwd.h"
#include "Data.h"
#include "Start.h"
#include "main.h"

int Callback3(void *para, int count, char **c_value, char **c_name)
{
    if(count != 0)
	{
	    return 1;
	}
	return 0;
}

int Change_Passwd::Function(int client_sock)
{
	Node user;
	sqlite3* db;
	char *etc = "etc/data.db";
	char *msg;
    char passwd[PASS_SIZE];
	char name[ACC_SIZE];
	char buffer[BUFF_SIZE];

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
	user.flag = sqlite3_exec(db,buffer,Callback3,NULL,&msg);	//查找用户名，密码是否匹配
	write(client_sock,&user,sizeof(user));
	strcpy(passwd,user.password);
	if(user.flag == 0)		//不匹配
	{
		sqlite3_close(db);
	    return 0;
	}
	else		//匹配
	{
	    read(client_sock,&user,sizeof(user));
		sprintf(buffer,"update user set password = '%s' where password = '%s' AND name = '%s'",user.password,passwd,name);
		user.flag = sqlite3_exec(db,buffer,NULL,NULL,&msg);		//跟新密码
		write(client_sock,&user,sizeof(user));
		sqlite3_close(db);
		return 0;
	}
	

}

Change_Passwd * Change_Passwd::Change_Passwd_ = NULL;

Change_Passwd * Change_Passwd::GetChange_Passwd()
{
	if(Change_Passwd_ == NULL)
	{
		Change_Passwd_ = new Change_Passwd();
	}

	return Change_Passwd_;
}
void Change_Passwd::FreeChange_Passwd()
{
	if(Change_Passwd_ != NULL)
	{
		delete Change_Passwd_;
		Change_Passwd_ = NULL;
	}
}


Change_Passwd::Change_Passwd()
{

}

