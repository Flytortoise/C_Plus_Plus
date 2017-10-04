#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include "My_Sql.h"
#include "MyTools.h"
#include "Hist.h"
#include "mark.h"

int Hist::Function(int client_sock)
{
    //printf("Hist funccccc!!!!!!\n");
    char get_len[5];
    int len;
    memset(get_len,0,sizeof(len));
    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Hist::_idd_len");
        return 0;
    }
    //printf("get_len = %s\n",get_len);

    len = atoi(get_len);
    _idd = new char[len + 1];
    memset(_idd,0,len + 1);
    rec = recv(client_sock,_idd,len,0);
    if(rec <  0)
    {
        perror("Hist::_idd:");
        return 0;
    }
    //printf("idd : %s\n",_idd);

    rec = recv(client_sock,&get_len,4,0);
    if(rec < 0)
    {
        perror("Hist::str1_len");
        return 0;
    }

    len = atoi(get_len);
    _str1 = new char[len + 1];
    memset(_str1,0,len + 1);
    rec = recv(client_sock,_str1,len,0);
    if(rec <  0)
    {
        perror("Hist::str1:");
        return 0;
    }

    rec = recv(client_sock,&get_len,4,0);
    if(rec < 0)
    {
        perror("Hist::str2_len");
        return 0;
    }

    len = atoi(get_len);
    _str2 = new char[len + 1];
    memset(_str2,0,len+ 1);
    rec = recv(client_sock,_str2,len,0);
    if(rec <  0)
    {
        perror("Hist::str2:");
        return 0;
    }


    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec <  0)
    {
        perror("Hist::_passwd:");
        return 0;
    }

    int s = DataBase();
    send(client_sock,&s,sizeof(s),0);

    if(s == HIST_SUCCESS)
    {
        int len = 0;
        char *buf;
        vector<string>::iterator t ;

        len = _LineInformation.size();
        buf = new char[len+1];
        strcpy(buf,_LineInformation.c_str());
        send(client_sock,&len,sizeof(len),0);
        send(client_sock,buf,len,0);
        delete []buf;

        for(t = _information.begin(); t != _information.end(); t++)
        {
            len = (*t).size();
            buf = new char[len+1];
            strcpy(buf,(*t).c_str());
            send(client_sock,&len,sizeof(len),0);
            send(client_sock,buf,len,0);
            delete []buf;
        }

        len = 0;    //发送结束标志
        send(client_sock,&len,sizeof(len),0);

    }

    return 0;
}

int Hist::DataBase()
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
            // 历史记录查询
            sprintf(buf,"select * from %s where Date between '%s' and '%s';"
                    ,name.c_str(),_str1,_str2);
            sql.MySql_exec(buf);
            _LineInformation = sql.GetLineInformation2();
            _information = sql.GetRowInformation2();

            if(_information.size() == 0)
            {
                result = NO_HISTORY;
            }
            else
            {
                result = HIST_SUCCESS;

            }
  //          std::cout << _LineInformation << std::endl;

        }

    }

    return result;

}


Hist * Hist::_Hist = NULL;
std::mutex Hist::_Hist_lock;

Hist * Hist::GetHist()
{
    std::unique_lock<std::mutex> lock(_Hist_lock);
    if(_Hist == NULL)
    {
        _Hist = new Hist();
    }

    return _Hist;
}
void Hist::FreeHist()
{
    std::unique_lock<std::mutex> lock(_Hist_lock);
    if(_Hist != NULL)
    {
        delete _Hist;
        _Hist = NULL;
    }
}


Hist::Hist() : _idd(NULL),_passwd(NULL),_str1(NULL),_str2(NULL)
{

}

Hist::~Hist()
{
    if(_idd != NULL)
    {
        delete []_idd;
    }

    if(_passwd != NULL)
    {
        delete []_idd;
    }

    if(_str1 != NULL)
    {
        delete []_idd;
    }

    if(_str2 != NULL)
    {
        delete []_idd;
    }

}
