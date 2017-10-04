#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <QDebug>

#include <sys/types.h>
#include <sys/socket.h>
#include "mark.h"
#include "Pass.h"
#include "MD5.h"

pass_ask::pass_ask() : _len(0)
{
    _passwd.clear();
    _name.clear();
}

void pass_ask::Init(char *name, char *passwd)
{
    _name = name;
    //qDebug() << passwd;
    _passwd = MD5(passwd).hexdigest();
    //qDebug() << _passwd.c_str();
    _len = _name.size();
}
/*
void pass_ask::SetFlag(int flag)
{
    _flag = flag;
}
*/
void pass_ask::Func(char **outstr, int flag)
{
    int max_len = _name.size()+22;
    //22中，1个字符给_len，16个给密码，还有1个给\0,4个给行为
    *outstr = new char[max_len];
    //qDebug() << sizeof(outstr);
    memset(*outstr,0,sizeof(*outstr));

    if(flag == 1)   //登录
    {
        snprintf(*outstr,max_len,"%s%d%s%s",LOG,_len-1,_name.c_str(),_passwd.c_str());
    }
    else
    {
        snprintf(*outstr,max_len,"%s%d%s%s",REGIST,_len-1,_name.c_str(),_passwd.c_str());
    }
    //qDebug() << *outstr;

}


Pass::Pass(int client,char *name, char *passwd) : client_sock(client)
{
    _ask.Init(name,passwd);
}

int Pass::Action(int flag)
{
    char *str;
    _ask.Func(&str, flag); //加密
    //qDebug() << str;
    //qDebug() << strlen(str);
    send(client_sock,str,strlen(str),0);
    //write(client_sock,str,strlen(str));	//发送给服务器进行处理
    //qDebug() << str;
    recv(client_sock,&_reply,sizeof(_reply),0);//读取服务器处理后的结果

    delete [] str;

    return _reply;

}


