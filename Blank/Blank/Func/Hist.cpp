#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include "Hist.h"
#include "MD5.h"
#include "mark.h"

void hist_ask::Init(char *idd, char *passwd, char *str1, char *str2)
{
    _idd.clear();
    _passwd.clear();
    _str1.clear();
    _str2.clear();

    _idd = idd;
    _str1 = str1;
    _str2 = str2;

    _idd_len = _idd.size();
    _str1_len = _str1.size();
    _str2_len = _str2.size();
    _passwd = MD5(passwd).hexdigest();
}

void hist_ask::Func(char **outstr)
{
    int max_len = _str1_len+_str2_len+ 34;
    //34中，4个给行为，4个给_str1_len，4个给_str2_len,4个iddlen
    //1个给\0，16个给密码

    *outstr = new char[max_len];
 //   memset(*outstr,0,sizeof(*outstr));
    snprintf(*outstr,max_len,"%s%04d%s%04d%s%04d%s%s",HIST,_idd_len,
             _idd.c_str(),_str1_len,
             _str1.c_str(),_str2_len,
             _str2.c_str(),_passwd.c_str());

    //qDebug() << *outstr;
}




int Hist::Function(int client_sock, char *idd, char *passwd, char *str1, char*str2)
{
    //printf("Hist funccccc!!!!!!\n");
    char *str;
    _ask.Init(idd,passwd,str1,str2);
    _ask.Func(&str);

    send(client_sock,str,strlen(str),0);

    recv(client_sock,&_result,sizeof(_result),0);

    if(_result == HIST_SUCCESS)
    {
        HandleInformation(client_sock);
    }

    delete []str;
    return _result;

}

string Hist::GetInformation()
{
    return _information;
}



void Hist::HandleInformation(int client_sock)
{
    char *buf;
    int len;
    _information.clear();

    recv(client_sock,&len,sizeof(len),0);
    while(len != 0)
    {
        buf = new char[len + 1];
        recv(client_sock,buf,len,0);
        //buf[len+1] = '\n';
        _information.append(buf);
        delete []buf;
        recv(client_sock,&len,sizeof(len),0);
    }

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


Hist::Hist()
{

}
