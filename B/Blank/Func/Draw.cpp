#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "MD5.h"
#include "Draw.h"
#include "mark.h"

void draw_ask::Init(char *idd, char *passwd, char *money)
{
    _idd.clear();
    _passwd.clear();
    _money.clear();

    _idd = idd;
    _passwd = MD5(passwd).hexdigest();
    _money = money;

    _idd_len = _idd.size();
    _money_len = _money.size();

}

void draw_ask::Func(char **outstr)
{
    int max_len = _idd_len  + _money_len + 29;
    //29个中，8个长度，4个操作，1个\0,16个密码
    *outstr = new char [max_len];
    snprintf(*outstr,max_len,"%s%04d%s%04d%s%s",
             DRAW,_idd_len,_idd.c_str(),_money_len,
             _money.c_str(),_passwd.c_str());

}


int Draw::Function(int client_sock, char *idd, char *passwd, char *money)
{
    //printf("Draw funccccc!!!!!!\n");

    char *str;
    _ask.Init(idd,passwd,money);
    _ask.Func(&str);

    send(client_sock,str,strlen(str),0);
    recv(client_sock,&_result,sizeof(_result),0);

    delete []str;

    return _result;
}

Draw * Draw::_Draw = NULL;
std::mutex Draw::_Draw_lock;

Draw * Draw::GetDraw()
{
    std::unique_lock<std::mutex> lock(_Draw_lock);
    if(_Draw == NULL)
    {
        _Draw = new Draw();
    }

    return _Draw;
}
void Draw::FreeDraw()
{
    std::unique_lock<std::mutex> lock(_Draw_lock);
    if(_Draw != NULL)
    {
        delete _Draw;
        _Draw = NULL;
    }
}


Draw::Draw()
{

}
