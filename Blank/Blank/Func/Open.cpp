#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Open.h"
#include "MD5.h"
#include "mark.h"

void open_ask::Init(char *name, char *id, char *passwd, char *money)
{
    _name.clear();
    _id.clear();
    _passwd.clear();
    _money.clear();

    _name = name;
    _id = id;
    _money = money;

    _name_len = _name.size();
    _money_len = _money.size();
    _passwd = MD5(passwd).hexdigest();
}

void open_ask::Func(char **outstr)
{
    int max_len = _name_len+_money_len+ 47;
    //47中，4个给行为，4个给name_len，4个给_money_len
    //1个给\0，16个给密码,18个id

    *outstr = new char[max_len];
 //   memset(*outstr,0,sizeof(*outstr));
    snprintf(*outstr,max_len,"%s%04d%s%04d%s%s%s",OPEN,_name_len,
             _name.c_str(),_money_len,
             _money.c_str(),_id.c_str(),_passwd.c_str());

    //qDebug() << *outstr;
}

Open::Open()
{

}

int Open::Function(int client_sock,char *name,char *passwd,char *id,char *money)
{
    //printf("Open funccccc!!!!!!\n");
    char *str;
    _ask.Init(name,id,passwd,money);
    _ask.Func(&str);

    send(client_sock,str,strlen(str),0);

    recv(client_sock,&_result,sizeof(_result),0);

    if(_result == REGIST_SUCCESS)
    {
        recv(client_sock,_idd,sizeof(_idd),0);
    }

    delete []str;
    return _result;
}



char *Open::GetIdd()
{
    return _idd;
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



