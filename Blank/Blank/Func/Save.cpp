#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Save.h"
#include "mark.h"

void save_ask::Init(char *idd, char *money)
{
    _idd.clear();
    _money.clear();;

    _idd = idd;
    _money = money;

    _idd_len = _idd.size();
    _money_len = _money.size();
}


void save_ask::Func(char **outstr)
{
    int max_len = _idd_len + _money_len + 13;
    //13中。4个iddlen，4个moneylen，1个\0,4个给操作

    *outstr = new char [max_len];
   // memset(*outstr,0,sizeof(*outstr));

    snprintf(*outstr,max_len,"%s%04d%s%04d%s",
               SAVE,_idd_len,_idd.c_str(),
             _money_len,_money.c_str());
}


int Save::Function(int client_sock, char *idd,char *money)
{
    char *str;
    _ask.Init(idd,money);
    _ask.Func(&str);

    send(client_sock,str,strlen(str),0);
    recv(client_sock,&_result,sizeof(_result),0);

    delete []str;
    return _result;
}

Save * Save::_Save = NULL;
std::mutex Save::_Save_lock;

Save * Save::GetSave()
{
    std::unique_lock<std::mutex> lock(_Save_lock);
    if(_Save == NULL)
    {
        _Save = new Save();
    }

    return _Save;
}

void Save::FreeSave()
{
    std::unique_lock<std::mutex> lock(_Save_lock);
    if(_Save != NULL)
    {
        delete _Save;
        _Save = NULL;
    }
}


Save::Save()
{

}
