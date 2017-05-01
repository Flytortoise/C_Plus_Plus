#include "Start.h"

#include <sqlite3.h>

extern pNode head;

int OffLine(void *para, int count, char **c_value, char **c_name)	
{
    int client_sock = *((int *)para);
	Node user;
	bzero(&user,sizeof(user));
	strcpy(user.name,c_value[0]);
	strcpy(user.buffer,c_value[1]);
	user.action = -5;
	write(client_sock,&user,sizeof(user));		//存在离线消息，则发送给该用户
	return 0;
}


void * Start(void *p)
{
	char *etc2 = "etc/temp.db";		//存放离线消息的数据库
	char *msg;
	sqlite3 *db2;

    int p_flag;		//退出登录的标志位
    int flag = SUCCESS;		//重复执行功能
	int client_sock = *((int *)p);	//当前客户端的套结字
	char buffer[BUFF_SIZE];
	pNode temp;		
	Node tmp;		//tmp保存是否被踢出功能的标志位

	Node pass;
	tmp.action = 1;
    
	while(1)
	{	
		p_flag = 0;		//初始化
		pass = Pass(client_sock);		//执行登录操作，返回用户登录的具体信息
		if(pass.action == -1)		//退出操作
		{
		    break;
		}

		//将正确登录的用户加入到在线用户链表中
		pNode user = (pNode)malloc(sizeof(Node));
		strcpy(user->name,pass.name);
		strcpy(user->id,pass.id);
		user->sock = client_sock;
		user->action = 1;
		user->chat_flag = 1;
		user->next = head->next;
		head->next = user;

		//打开离线消息数据库，查找，是否有该用户的离线消息
		sqlite3_open(etc2,&db2);
		sprintf(buffer,"select * from _%s",user->name);
		sqlite3_exec(db2,buffer,OffLine,(void *)&client_sock,&msg);
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"drop table _%s",user->name);
		sqlite3_exec(db2,buffer,NULL,NULL,&msg);	//处理完毕后，销毁离线消息
		sqlite3_close(db2);

		
		temp = head->next;
		while(temp != NULL)		//找到当前用户的结点
		{
			if(temp->sock == client_sock)
			{
				break;
			}
			temp = temp->next;
		}

		while(flag == SUCCESS)		//具体功能入口
		{
			write(client_sock,temp,sizeof(Node));	//将当前用户信息发送个客户端
			if(strcmp(pass.name,"root") == 0)		//判断是否为超级用户
			{
				p_flag = Select_func2(client_sock,&flag);	//执行具体功能
				read(client_sock,&tmp,sizeof(Node));	//tmp保存是否被踢出功能的标志位
				if(p_flag == -1 || tmp.flag == 0)		//执行退出登录或者被管理员提出，则回到用户登录
				{
				    break;
				}
			}
			else
			{
				p_flag = Select_func(client_sock,&flag);	//执行具体功能
				read(client_sock,&tmp,sizeof(Node));	//tmp保存是否被踢出功能的标志位
				if(p_flag == -1 || tmp.flag == 0)		//执行退出登录或者被管理员提出，则回到用户登录
				{
				    break;
				}
			}
    	}

		if(flag == 0)		//执行退出聊天室功能，则退出
		{
		    break;
		}
		
	}

	return NULL;
}
