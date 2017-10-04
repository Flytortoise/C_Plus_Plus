#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ChPw.h"

#include "MD5.h"
#include "mark.h"

void chpw_ask::Init(char *idd, char *passwd, char *newpasswd)
{
    _idd.clear();
    _passwd.clear();
    _new_passwd.clear();

    _idd = idd;

    _idd_len = _idd.size();
    _passwd = MD5(passwd).hexdigest();
    _new_passwd = MD5(newpasswd).hexdigest();
}

void chpw_ask::Func(char **outstr)
{
    int max_len = _idd_len+ 41;
    //41中，4个给行为，4个给idd_len
    //1个给\0，32个给密码

    *outstr = new char[max_len];
 //   memset(*outstr,0,sizeof(*outstr));
    sprintf(*outstr,"%s%04d%s",CHPW,_idd_len,_idd.c_str());
    strncat(*outstr,_passwd.c_str(),16);
    strncat(*outstr,_new_passwd.c_str(),16);

    //qDebug() << *outstr;
}


int ChPw::Function(int client_sock, char *idd, char *passwd, char *newpasswd)
{
    //printf("ChPw funccccc!!!!!!\n");
    char *str;
    _ask.Init(idd,passwd,newpasswd);
    _ask.Func(&str);

    send(client_sock,str,strlen(str),0);

    recv(client_sock,&_result,sizeof(_result),0);


    delete []str;
    return _result;
}

ChPw * ChPw::_ChPw = NULL;
std::mutex ChPw::_ChPw_lock;

ChPw * ChPw::GetChPw()
{
    std::unique_lock<std::mutex> lock(_ChPw_lock);
    if(_ChPw == NULL)
    {
        _ChPw = new ChPw();
    }

    return _ChPw;
}
void ChPw::FreeChPw()
{
    std::unique_lock<std::mutex> lock(_ChPw_lock);
    if(_ChPw != NULL)
    {
        delete _ChPw;
        _ChPw = NULL;
    }
}


ChPw::ChPw()
{

}
