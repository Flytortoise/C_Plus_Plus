#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Regi.h"
#include "mark.h"
#include "My_Sql.h"
#include "Pass.h"
#include "MyTools.h"

int Regi::Function(int client_sock)
{
    char len;
    int rec = -1;
    while(rec < 0 )
    {
        rec = recv(client_sock,&len,sizeof(char),0);    //由于sock是非阻塞，因此要循环读取数据
    }

    len++;  //用户名长度在客户端处，自减了1
    _name = new char[len - '0' + 1];
    memset(_name,0,len - '0' + 1);
    rec = recv(client_sock,_name,len - '0',0);
    if(rec < 0)
    {
        perror("Regi::name :");
        return 0;
    }

    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec < 0)
    {
        perror("Regi::passwd ; ");
        return 0;
    }

    int s = DateBase();

    send(client_sock,&s,sizeof(s),0);
    //printf("%c name:%s passwd:%s\n",len,_name,_passwd);

    return 0;
}

int Regi::DateBase()
{
    int result = 0;
    char buf[100];
    int flag = 0;
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
        //可以注册
        sprintf(buf,"insert into manager values( 0 ,\"%s\",\"%s\");",_name,_passwd);
       // printf("buf = %s\n",buf);
        sql.MySql_exec(buf);
        //printf("ret = %d\n",ret);
        result = REGIST_SUCCESS;
    }
    else
    {
        result = HAS_ACCOUNT;
    }
   // printf("buf2 = %s",buf);
   // printf("res = %d\n",result);
    return result;
}


Regi * Regi::_Regi = NULL;
std::mutex Regi::_Regi_lock;

Regi * Regi::GetRegi()
{
    std::unique_lock<std::mutex> lock(_Regi_lock);
    if(_Regi == NULL)
    {
        _Regi = new Regi();
    }

    return _Regi;
}
void Regi::FreeRegi()
{
    std::unique_lock<std::mutex> lock(_Regi_lock);
    if(_Regi != NULL)
    {
        delete _Regi;
        _Regi = NULL;
    }
}


Regi::Regi(){ }
