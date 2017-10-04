#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <QDebug>
#include "Dest.h"
#include "mark.h"
#include "MD5.h"

void dest_ask::Init(char *idd, char *passwd)
{
    _idd.clear();
    _passwd.clear();

    _idd = idd;
    _passwd = MD5(passwd).hexdigest();

    _idd_len = _idd.size();

}

void dest_ask::Func(char **outstr)
{
    int max_len = _idd_len + 25;
    //25个中，4个长度，4个操作，1个\0,16个密码
    *outstr = new char [max_len];
    snprintf(*outstr,max_len,"%s%04d%s%s",
             DEST,_idd_len,_idd.c_str(),_passwd.c_str());

}



int Dest::Function(int client_sock, char *_idd,char *passwd)
{
    //printf("Dest funccccc!!!!!!\n");
    char *str;
    _ask.Init(_idd,passwd);
    _ask.Func(&str);
   // qDebug() << str;
    send(client_sock,str,strlen(str),0);
    recv(client_sock,&_result,sizeof(_result),0);

    delete []str;

    return _result;
}

Dest * Dest::_Dest = NULL;
std::mutex Dest::_Dest_lock;

Dest * Dest::GetDest()
{
    std::unique_lock<std::mutex> lock(_Dest_lock);
    if(_Dest == NULL)
    {
        _Dest = new Dest();
    }

    return _Dest;
}
void Dest::FreeDest()
{
    std::unique_lock<std::mutex> lock(_Dest_lock);
    if(_Dest != NULL)
    {
        delete _Dest;
        _Dest = NULL;
    }
}


Dest::Dest()
{

}


