#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "My_Sql.h"
#include "MyTools.h"
#include "Inqu.h"
#include "mark.h"

int Inqu::Function(int client_sock)
{
    //printf("Inqu funccccc!!!!!!\n");
    char get_len[5];
    int len;

    memset(get_len,0,sizeof(get_len));
    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Inqu::_idd_len");
        return 0;
    }

    len = atoi(get_len);
    _idd = new char[len + 1];
    memset(_idd,0,len + 1);
    rec = recv(client_sock,_idd,len,0);
    if(rec <  0)
    {
        perror("Inqu::_idd:");
        return 0;
    }

    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec <  0)
    {
        perror("Inqu::_passwd:");
        return 0;
    }

    int s = DataBase();
    send(client_sock,&s,sizeof(s),0);
    if(s == INQU_SUCCESS)
    {
        char t[30];
        strcpy(t,_money.c_str());
        send(client_sock,t,sizeof(t),0);
    }

    return 0;
}

int Inqu::DataBase()
{
    int result = 0;
    char buf[1024]; //必须足够大，不然出现内存不足

    int flag = 0;   //在数据库中存在的标志位
    My_Sql sql("Blank");
    vector<string> temp;

    sprintf(buf,"select name from user_information where idd = %s;",_idd);
    sql.MySql_exec(buf);
    temp = sql.GetRowInformation();

    if(temp.size() == 0)  //该处，判断内容有无，有待优化!
    {
        //无帐号
        result = NO_ACCOUNT;
    }
    else
    {
        string name = temp[0];
        sprintf(buf,"select passwd = \"%s\" from user_information where idd = %s;",_passwd,_idd);

        sql.MySql_exec(buf);
        temp = sql.GetRowInformation();
        MyTools tool;
        flag = tool.DataHandle(temp);
        if(flag == 0)  //密码错误
        {
            result = PASSWD_ERROR;
        }
        else
        {
            //查询
            sprintf(buf,"select money from %s where number = (select max(number) from %s);",
                  name.c_str(),name.c_str());
            sql.MySql_exec(buf);
            temp = sql.GetRowInformation();
            _money = temp[0];

            result = INQU_SUCCESS;

        }

    }

    return result;

}


Inqu * Inqu::_Inqu = NULL;
std::mutex Inqu::_Inqu_lock;

Inqu * Inqu::GetInqu()
{
    std::unique_lock<std::mutex> lock(_Inqu_lock);
    if(_Inqu == NULL)
    {
        _Inqu = new Inqu();
    }

    return _Inqu;
}
void Inqu::FreeInqu()
{
    std::unique_lock<std::mutex> lock(_Inqu_lock);
    if(_Inqu != NULL)
    {
        delete _Inqu;
        _Inqu = NULL;
    }
}


Inqu::Inqu() : _idd(NULL),_passwd(NULL)
{

}

Inqu::~Inqu()
{
    if(_idd != NULL)
    {
        delete []_idd;
    }

    if(_passwd != NULL)
    {
        delete []_passwd;
    }
}
