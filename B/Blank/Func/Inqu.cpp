#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "MD5.h"
#include "mark.h"

#include "Inqu.h"

void inqu_ask::Init(char *idd, char *passwd)
{
    _idd.clear();
    _passwd.clear();

    _idd = idd;

    _idd_len = _idd.size();

    _passwd = MD5(passwd).hexdigest();
}

void inqu_ask::Func(char **outstr)
{
    int max_len = _idd_len + 25;
    //25中，4个给行为，4个给idd_len
    //1个给\0，16个给密码,

    *outstr = new char[max_len];
 //   memset(*outstr,0,sizeof(*outstr));
    snprintf(*outstr,max_len,"%s%04d%s%s",INQU,_idd_len,
             _idd.c_str(),_passwd.c_str());

    //qDebug() << *outstr;
}


int Inqu::Function(int client_sock, char *idd, char *passwd)
{
   // printf("Inqu funccccc!!!!!!\n");

    char *str;
    _ask.Init(idd,passwd);
    _ask.Func(&str);

    send(client_sock,str,strlen(str),0);

    recv(client_sock,&_result,sizeof(_result),0);

    if(_result == INQU_SUCCESS)
    {
        _money = new char[30];
        recv(client_sock,_money,30,0);
    }

    delete []str;
    return _result;

}


char *Inqu::GetMoney()
{
    return _money;
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


Inqu::Inqu() : _money(NULL)
{

}

Inqu::~Inqu()
{
    if(_money != NULL)
    {
        delete [] _money;
    }
}
