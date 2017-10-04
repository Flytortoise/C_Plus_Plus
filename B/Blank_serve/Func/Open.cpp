#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Open.h"
#include "MyTools.h"
#include "My_Sql.h"
#include "mark.h"

using namespace std;

int Open::Function(int client_sock)
{
    //printf("Open funccccc!!!!!!\n");

    char get_len[5];
    int len;

    memset(get_len,0,sizeof(get_len));
   // char buf[100];
    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Open :: name_len :");
        return 0;
    }

    len = atoi(get_len);
    _name = new char[len+ 1];
    memset(_name,0,len + 1);
    rec = recv(client_sock,_name,len,0);
    if(rec < 0)
    {
        perror("Open::name :");
        return 0;
    }

    rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Open :: money_len :");
        return 0;
    }

    len = atoi(get_len);
    _money = new char[len + 1];
    memset(_money,0,len+ 1);
    rec = recv(client_sock,_money,len,0);
    if(rec < 0)
    {
        perror("Open::_money :");
        return 0;
    }

    _id = new char[19];
    memset(_id,0,19);
    rec = recv(client_sock,_id,18,0);
    if(rec < 0)
    {
        perror("Open::id : ");
        return 0;
    }

    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec < 0)
    {
        perror("Open::passwd : ");
        return 0;
    }

 //   printf("name:%s\n",_name);
 //   printf("id:%s\n",_id);
 //   printf("passwd:%s\n",_passwd);
 //   printf("money:%s\n",_money);

 //读取数据完毕，进行数据库处理

    int s = DataBase();

    send(client_sock,&s,sizeof(s),0);

    if(s == REGIST_SUCCESS)
    {
        send(client_sock,_idd,sizeof(_idd),0);

    }

    return 0;
}


int Open::DataBase()
{
    int result = 0;
    char buf[1024]; //必须足够大，不然出现内存不足

    int flag = 0;   //在数据库中存在的标志位
    My_Sql sql("Blank");
    vector<string> temp;

     //××××××××××××××××××××××××
    //这里要换成ID以后
    sprintf(buf,"select name = \"%s\" from user_information;",_name);
    //××××××××××××××××××××××××××××××

    sql.MySql_exec(buf);
    temp = sql.GetRowInformation();
    MyTools tool;
    flag = tool.DataHandle(temp);

    if(flag == 0)  //该处，判断内容有无，有待优化!
    {
        //可以注册
        sprintf(buf,"insert into user_information (id,name,passwd,action,money) values( \"%s\",\"%s\",\"%s\",\"%s\",\"%s\");",_id,_name,_passwd,OPEN,_money);
        sql.MySql_exec(buf);    //该处没判断

        sprintf(buf,"select idd from user_information where name = \"%s\";",_name);
        sql.MySql_exec(buf);
        temp = sql.GetRowInformation();
        strcpy(_idd,temp[0].c_str());
        result = REGIST_SUCCESS;

        sprintf(buf,"create table %s(\
                    number int unsigned not null auto_increment primary key,\
                    action char(10) not null default '0',\
                    OtherID int unsigned not null default 0,\
                    cmoney double(10,3) not null default 0,\
                    money double(10,3) not null default 0,\
                    Date timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP \
                );",_name);
        sql.MySql_exec(buf);
        sprintf(buf,"insert into %s (action,money)\
                     values( \"%s\",%s);",
                _name,OPEN,_money);
        sql.MySql_exec(buf);

    }
    else
    {
        result = HAS_ACCOUNT;
    }

    return result;
}


Open * Open::_Open = NULL;
std::mutex Open::_Open_lock;

Open * Open::GetOpen()
{
    std::unique_lock<std::mutex> lock(_Open_lock);
    if(_Open == NULL)
    {
        _Open = new Open();
    }

    return _Open;
}
void Open::FreeOpen()
{
    std::unique_lock<std::mutex> lock(_Open_lock);
    if(_Open != NULL)
    {
        delete _Open;
        _Open = NULL;
    }
}


Open::Open() : _name(NULL),_passwd(NULL),_money(NULL),_id(NULL)
{

}

Open::~Open()
{
    if(_name != NULL)
    {
        delete []_name;
    }

    if(_passwd != NULL)
    {
        delete []_passwd;
    }

    if(_money != NULL)
    {
        delete []_money;
    }

    if(_id != NULL)
    {
        delete []_id;
    }
}
