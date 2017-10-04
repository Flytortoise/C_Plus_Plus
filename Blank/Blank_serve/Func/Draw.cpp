#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "My_Sql.h"
#include "MyTools.h"
#include "Draw.h"
#include "mark.h"

int Draw::Function(int client_sock)
{
    //printf("Draw funccccc!!!!!!\n");
    char get_len[5];
    int len;
    memset(get_len,0,sizeof(get_len));
    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Draw::idd_len");
        return 0;
    }

    len = atoi(get_len);
    _idd = new char[len + 1];
    memset(_idd,0,len + 1);
    rec = recv(client_sock,_idd,len,0);
    if(rec <  0)
    {
        perror("Draw::_idd:");
        return 0;
    }

    rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Draw::money_len");
        return 0;
    }

    len = atoi(get_len);
    _money = new char[len+ 1];
    memset(_money,0,len+ 1);
    rec = recv(client_sock,_money,len,0);
    if(rec <  0)
    {
        perror("Draw::_money:");
        return 0;
    }

    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec <  0)
    {
        perror("Draw::_passwd:");
        return 0;
    }

    int s = DataBase();
    send(client_sock,&s,sizeof(s),0);

    return 0;
}

int Draw::DataBase()
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
            sprintf(buf,"select money from %s where number = (select max(number) from %s);",
                  name.c_str(),name.c_str());
            sql.MySql_exec(buf);
            temp = sql.GetRowInformation();

            double mon = atof(temp[0].c_str()) - atof(_money);

            if(mon < 0)    //余额不足
            {
                result = NO_MONEY;
            }
            else        //取款成功
            {
                sprintf(buf,"insert into %s (money,cmoney,action) \
                                        values (%f,'%s','%s');",
                        name.c_str(),mon,_money,DRAW);
                sql.MySql_exec(buf);
                result = DRAW_SUCCESS;
            }
        }

    }

    return result;

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

Draw::~Draw()
{
    if(_idd != NULL)
    {
        delete []_idd;
    }

    if(_passwd != NULL)
    {
        delete []_passwd;
    }

    if(_money != NULL)
    {
        delete []_money;
    }
}


Draw::Draw() : _idd(NULL),_passwd(NULL),_money(NULL)
{

}
