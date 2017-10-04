#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <QDebug>
#include "Tran.h"
#include "mark.h"
#include "MD5.h"

void tran_ask::Init(char *my_idd, char *passwd, char *money,char *other_idd)
{
    _my_idd.clear();
    _passwd.clear();
    _money.clear();
    _other_idd.clear();

    _my_idd = my_idd;
    _passwd = MD5(passwd).hexdigest();
    _money = money;
    _other_idd = other_idd;

    _my_idd_len = _my_idd.size();
    _money_len = _money.size();
    _other_idd_len = _other_idd.size();

}

void tran_ask::Func(char **outstr)
{
    int max_len = _my_idd_len  + _money_len + _other_idd_len +33;
    //33个中，12个长度，4个操作，1个\0,16个密码
    *outstr = new char [max_len];
    snprintf(*outstr,max_len,"%s%04d%s%04d%s%04d%s%s",
             TRAN,_my_idd_len,_my_idd.c_str(),_money_len,
             _money.c_str(),_other_idd_len,_other_idd.c_str(),_passwd.c_str());

}



int Tran::Function(int client_sock, char *my_idd,char *passwd, char *money, char *other_idd)
{
    //printf("Tran funccccc!!!!!!\n");
    char *str;
    _ask.Init(my_idd,passwd,money,other_idd);
    _ask.Func(&str);
   // qDebug() << str;
    send(client_sock,str,strlen(str),0);
    recv(client_sock,&_result,sizeof(_result),0);

    delete []str;

    return _result;
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


Tran::Tran()
{

}
