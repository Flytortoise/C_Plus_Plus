#include "My_Sql.h"

#include <iostream>

#define USERNAME "root"
#define DATAPASSWD "123456"

using namespace std;

My_Sql::My_Sql(char *Db_name)
{
    _mysql = mysql_init(NULL);
    if(_mysql == NULL)
    {
        printf ("mysql_init error: %s\n", mysql_error(_mysql));
        exit(-1);
    }

    // 连接服务器
    MYSQL * conn = mysql_real_connect(_mysql, "localhost", USERNAME, DATAPASSWD, Db_name, 0, NULL, 0);
    if(conn == NULL)
    {
        printf ("mysql_init error: %s\n", mysql_error(_mysql));
        exit(-1);
    }


    // 设置中文显示
    //mysql_query(_mysql, "set names utf8");
    //printf ("连上my_db......\n");

}


// 成功返回0， 失败返回-1
int My_Sql::MySql_exec(const char *sql)
{
    //  mysql语句执行

    printf("sql : %s\n",sql);

    int ret = mysql_query(_mysql, sql);
    if (ret != 0)
    {
        printf ("mysql_query error: %s\n", mysql_error(_mysql));
        return -1;
    }

// 从服务器下载数据到本地
//mysql_store_result()将查询的全部结果读取到客户端，分配1个MYSQL_RES结构，并将结果置于该结构中。
    _mysql_res = mysql_store_result(_mysql);

    if (_mysql_res == NULL)
    {
        // 并没有发生错误，只是没有取到值而已
        if (mysql_errno(_mysql) == 0)
        {
                printf ("Query OK!\n");
                return 0;
        }
        else
        {
                printf ("mysql_store_result error: %s\n", mysql_error(_mysql));
                return -1;
        }
    }

    // 获取列数
    _num_fields =  mysql_num_fields(_mysql_res);

    // 获取每一列的字段
    //返回所有MYSQL_FIELD结构的数组。每个结构提供了结果集中1列的字段定义。
    _field = mysql_fetch_fields(_mysql_res);
//    printf("%s--%d",__FILE__,__LINE__);
    return 1;
}

My_Sql::~My_Sql()
{
    mysql_free_result(_mysql_res);
}

string My_Sql::GetLineInformation()
{
    _line_information.clear();  //将上一次数据清理
    for (unsigned int i = 0; i < _num_fields; i++)
    {
            _line_information = _line_information + _field[i].name;
    }
 //   std::cout << "line : " << _line_information << std::endl;

    return _line_information;
}

vector<string> My_Sql::GetRowInformation()
{
    string temp;
  //  printf("%s--%d\n",__FILE__,__LINE__);
    _row_information.clear();   //将上一次数据清理
    // 一行一行处理数据
    //下一行的MYSQL_ROW结构。如果没有更多要检索的行或出现了错误，返回NULL。
    while((_row = mysql_fetch_row(_mysql_res)))
    {
        temp.clear();   //将上一次数据清理

        for (unsigned int i = 0; i < _num_fields; i++)
        {
                temp = temp + _row[i];
    //            cout << "temp " << temp << endl;
        }
        //printf("%s--%d\n",__FILE__,__LINE__);

        _row_information.push_back(temp);

   //     printf("%s--%d\n",__FILE__,__LINE__);


    }
  //  printf("%s--%d\n",__FILE__,__LINE__);

    return _row_information;
}


string My_Sql::GetLineInformation2()
{
    char buff[1024];
    memset(buff,0,sizeof(buff));
    _line_information.clear();  //将上一次数据清理
    for (unsigned int i = 0; i < _num_fields; i++)
    {
        sprintf(buff,"%-15s",_field[i].name);
        _line_information.append(buff);
    }
    _line_information.append("\n");
    return _line_information;
}

vector<string> My_Sql::GetRowInformation2()
{
    string temp;
    char buff[1024];
    memset(buff,0,sizeof(buff));

    _row_information.clear();   //将上一次数据清理
    // 一行一行处理数据
    //下一行的MYSQL_ROW结构。如果没有更多要检索的行或出现了错误，返回NULL。
    while((_row = mysql_fetch_row(_mysql_res)))
    {
        temp.clear();   //将上一次数据清理

        for (unsigned int i = 0; i < _num_fields; i++)
        {
            sprintf(buff,"%-15s",_row[i]);
            temp.append(buff);
        }
        temp.append("\n");
        _row_information.push_back(temp);

    }

    return _row_information;
}


