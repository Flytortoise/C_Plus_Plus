#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <vector>
#include "Save.h"
#include "My_Sql.h"
#include "mark.h"
#include "MyTools.h"

using namespace std;

int Save::Function(int client_sock)
{
    //printf("Save funccccc!!!!!!\n");

    char get_len[5];
    int len;
    memset(get_len,0,sizeof(get_len));

    int rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Save::idd_len");
        return 0;
    }

    len = atoi(get_len);
    _idd = new char[len+ 1];
    memset(_idd,0,len  + 1);
    rec = recv(client_sock,_idd,len,0);
    if(rec <  0)
    {
        perror("Save::_idd:");
        return 0;
    }

    rec = recv(client_sock,get_len,4,0);
    if(rec < 0)
    {
        perror("Save::money_len");
        return 0;
    }


    len = atoi(get_len);
    _money = new char[len+ 1];
    memset(_money,0,len+ 1);
    rec = recv(client_sock,_money,len,0);
    if(rec <  0)
    {
        perror("Save::_money:");
        return 0;
    }

    int s = DataBase();
    send(client_sock,&s,sizeof(s),0);

    return 0;
}

int Save::DataBase()
{
    int result = 0;
    char buf[1024]; //必须足够大，不然出现内存不足

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
        //存款
         string name = temp[0];
        sprintf(buf,"select money from %s where number = (select max(number) from %s);",
                name.c_str(),name.c_str());
        sql.MySql_exec(buf);
        temp = sql.GetRowInformation();

        double mon = atof(temp[0].c_str()) + atof(_money);


        sprintf(buf,"insert into %s (money,cmoney,action) \
                                values (%f,'%s','%s');",
                name.c_str(),mon,_money,SAVE);
        sql.MySql_exec(buf);
        result = SAVE_SUCCESS;
    }

    return result;

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


Save::Save():_idd(NULL),_money(NULL)
{

}

Save::~Save()
{
    if(_idd != NULL)
    {
        delete []_idd;
    }

    if(_money != NULL)
    {
        delete []_money;
    }
}
