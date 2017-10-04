#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ChPw.h"
#include "MyTools.h"
#include "My_Sql.h"
#include "mark.h"

int ChPw::Function(int client_sock)
{
    //printf("ChPw funccccc!!!!!!\n");
    char get_len[5];
    int len;
    memset(get_len,0,sizeof(get_len));
   // char buf[100];
    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("ChPw :: idd_len :");
        return 0;
    }

    len = atoi(get_len);
    _idd = new char[len+ 1];
    memset(_idd,0,len+ 1);
    rec = recv(client_sock,_idd,len,0);
    if(rec < 0)
    {
        perror("ChPw::_idd :");
        return 0;
    }


    _passwd = new char[17];
    memset(_passwd,0,17);
    rec = recv(client_sock,_passwd,16,0);
    if(rec < 0)
    {
        perror("ChPw::passwd : ");
        return 0;
    }

    _new_passwd = new char[17];
    memset(_new_passwd,0,17);
    rec = recv(client_sock,_new_passwd,16,0);
    if(rec < 0)
    {
        perror("ChPw::_new_passwd : ");
        return 0;
    }


 //读取数据完毕，进行数据库处理

    int s = DataBase();
   // printf("%s----%d\n",__FILE__,__LINE__);
    send(client_sock,&s,sizeof(s),0);

    return 0;
}


int ChPw::DataBase()
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
            //修改密码
            sprintf(buf,"update user_information set passwd = '%s' where idd = %s;",_new_passwd,_idd);
            sql.MySql_exec(buf);

            result = CHPW_SUCCESS;

        }

    }
   // printf("%s----%d\n",__FILE__,__LINE__);
    return result;

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


ChPw::ChPw() : _idd(NULL),_passwd(NULL),_new_passwd(NULL)
{

}

ChPw::~ChPw()
{
    if(_idd != NULL)
    {
        delete []_idd;
    }

    if(_passwd != NULL)
    {
        delete []_passwd;
    }

    if(_new_passwd != NULL)
    {
        delete []_new_passwd;
    }

}

