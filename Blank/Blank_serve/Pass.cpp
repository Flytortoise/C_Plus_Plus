#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Pass.h"
#include "My_Sql.h"
#include "MyTools.h"
#include "mark.h"

Pass::Pass(){}

Pass * Pass::_Pass = NULL;
std::mutex Pass::_Pass_lock;

Pass * Pass::GetPass()
{
    std::unique_lock<std::mutex> lock(_Pass_lock);
    if(_Pass == NULL)
    {
        _Pass = new Pass();
    }

    return _Pass;
}

void Pass::FreePass()
{
    std::unique_lock<std::mutex> lock(_Pass_lock);
    if(_Pass != NULL)
    {
        delete _Pass;
        _Pass = NULL;
    }
}

int Pass::Function(int client_sock)
{
    char len;
    int rec = -1;
    while(rec < 0 )
    {
        rec = recv(client_sock,&len,sizeof(char),0);    //由于sock是非阻塞，因此要循环读取数据
    }

    len++;  //用户名长度在客户端处，自减了1
    //printf("len = %d\n",len - '0');

    _name = new char[len - '0' + 1];
    memset(_name,0,len - '0' + 1);
    rec = recv(client_sock,_name,len - '0',0);
    if(rec < 0)
    {
        perror("Pass::name :");
        return 0;
    }
    //printf("name = %s\n",_name);
    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec < 0)
    {
        perror("Pass::passwd : ");
        return 0;
    }

    int s = DateBase();

    send(client_sock,&s,sizeof(s),0);
    //printf("%c name:%s passwd:%s\n",len,_name,_passwd);

    return 0;
}

int Pass::DateBase()
{
    int result = 0;
    char buf[100];

    int flag = 0;   //在数据库中存在的标志位
    My_Sql sql("Blank");
    vector<string> temp;

    sprintf(buf,"select name = \"%s\" from manager;",_name);
    //printf("buf = %s\n",buf);
    sql.MySql_exec(buf);
    temp = sql.GetRowInformation();
    MyTools tool;
    flag = tool.DataHandle(temp);

    if(flag == 0)  //该处，判断内容有无，有待优化!
    {
        result = NO_ACCOUNT;    //无用户名，未注册
    }
    else
    {
        sprintf(buf,"select name = \"%s\" AND passwd = \"%s\" from manager;",_name,_passwd);
        sql.MySql_exec(buf);
        flag = 0;
        temp = sql.GetRowInformation();
        MyTools tool;
        flag = tool.DataHandle(temp);
        if(flag == 0)
        {
            result = PASSWD_ERROR;  // 存在用户，密码错误
        }
        else
        {
            result = LOG_SUCCESS;   //登录成功
        }
    }
   // printf("buf2 = %s",buf);
   // printf("res = %d\n",result);
    return result;
}


