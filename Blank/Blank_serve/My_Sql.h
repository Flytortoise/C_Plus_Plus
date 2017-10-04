#ifndef MY_SQL_H
#define MY_SQL_H

#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

class My_Sql
{
public:
    My_Sql(char *Db_name);
    ~My_Sql();
    int MySql_exec(const char *sql);
    string GetLineInformation();
    vector<string> GetRowInformation();
    string GetLineInformation2();
    vector<string> GetRowInformation2();

private:
    MYSQL *_mysql;
    MYSQL_RES *_mysql_res;   //执行结果
    unsigned int _num_fields;   //列数
    MYSQL_FIELD *_field;    //字段
    MYSQL_ROW _row;     //一行行的数据

    string _line_information;   //字段信息
    vector<string> _row_information;    //所有的结果数据
};

#endif // MY_SQL_H
