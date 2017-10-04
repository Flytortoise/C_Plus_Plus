#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "My_Sql.h"
#include "MyTools.h"
#include "Tran.h"
#include "mark.h"


int Tran::Function(int client_sock)
{
    //printf("Tran funccccc!!!!!!\n");
    char get_len[5];
    int len;
    memset(get_len,0,sizeof(get_len));

    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Tran::my_idd_len");
        return 0;
    }

    len = atoi(get_len);
    _my_idd = new char[len + 1];
    memset(_my_idd,0,len + 1);
    rec = recv(client_sock,_my_idd,len,0);
    if(rec <  0)
    {
        perror("Tran::_my_idd:");
        return 0;
    }

    rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Tran::money_len");
        return 0;
    }

    len = atoi(get_len);
    _money = new char[len + 1];
    memset(_money,0,len + 1);
    rec = recv(client_sock,_money,len,0);
    if(rec <  0)
    {
        perror("Tran::_money:");
        return 0;
    }

    rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Tran::other_idd_len");
        return 0;
    }

    len = atoi(get_len);
    _other_idd = new char[len + 1];
    memset(_other_idd,0,len + 1);
    rec = recv(client_sock,_other_idd,len,0);
    if(rec <  0)
    {
        perror("Tran::other_idd:");
        return 0;
    }


    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec <  0)
    {
        perror("Tran::_passwd:");
        return 0;
    }

    int s = DataBase();
    send(client_sock,&s,sizeof(s),0);

    return 0;
}

int Tran::DataBase()
{
    int result = 0;
    char buf[1024]; //必须足够大，不然出现内存不足

    int flag = 0;   //在数据库中存在的标志位
    My_Sql sql("Blank");
    vector<string> temp;

    sprintf(buf,"select name from user_information where idd = %s;",_my_idd);
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
        sprintf(buf,"select passwd = \"%s\" from user_information where idd = %s;",_passwd,_my_idd);

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
            sprintf(buf,"select name from user_information where idd = %s;",_other_idd);
            sql.MySql_exec(buf);
            temp = sql.GetRowInformation();


            if(temp.size() == 0)   //无对方账户
            {
                result = NO_OTHER_ACCOUNT;
            }
            else
            {
                string name2 = temp[0];
                sprintf(buf,"select money from %s where number = (select max(number) from %s);",
                      name.c_str(),name.c_str());
                sql.MySql_exec(buf);
                temp = sql.GetRowInformation();

                double mon = atof(temp[0].c_str()) - atof(_money);

                if(mon < 0)    //余额不足
                {
                    result = NO_MONEY;
                }
                else
                {
                   //己方账户减钱
                    sprintf(buf,"insert into %s (money,cmoney,action,OtherID) \
                                            values (%f,-'%s','%s','%s');",
                            name.c_str(),mon,_money,TRAN,_other_idd);
                    sql.MySql_exec(buf);

                   //对方账户加钱
                    sprintf(buf,"select money from %s where number = (select max(number) from %s);",
                          name2.c_str(),name2.c_str());
                    sql.MySql_exec(buf);
                    temp = sql.GetRowInformation();

                    mon = atof(temp[0].c_str()) + atof(_money);
                    sprintf(buf,"insert into %s (money,cmoney,action,OtherID) \
                                            values (%f,+'%s','%s','%s');",
                            name2.c_str(),mon,_money,TRAN,_my_idd);
                    sql.MySql_exec(buf);

                    result = TRAN_SUCCESS;
                }


            }

        }

    }

    return result;

}




Tran * Tran::_Tran = NULL;
std::mutex Tran::_Tran_lock;

Tran * Tran::GetTran()
{
    std::unique_lock<std::mutex> lock(_Tran_lock);
    if(_Tran == NULL)
    {
        _Tran = new Tran();
    }

    return _Tran;
}
void Tran::FreeTran()
{
    std::unique_lock<std::mutex> lock(_Tran_lock);
    if(_Tran != NULL)
    {
        delete _Tran;
        _Tran = NULL;
    }
}


Tran::~Tran()
{
    if(_my_idd != NULL)
    {
        delete []_my_idd;
    }

    if(_other_idd != NULL)
    {
        delete []_other_idd;
    }

    if(_passwd != NULL)
    {
        delete []_passwd;
    }

    if(_money != NULL)
    {
        delete []_money;
    }
}


Tran::Tran() : _my_idd(NULL),_other_idd(NULL),
                _passwd(NULL),_money(NULL)
{

}
