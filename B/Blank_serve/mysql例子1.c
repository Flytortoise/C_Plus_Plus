#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>

#define MY_DB "my_db"

MYSQL *init()
{
    MYSQL *mysql = mysql_init(NULL);
    if(mysql == NULL)
    {
            printf ("mysql_init error: %s\n", mysql_error(mysql));
            return NULL;
    }

    // 连接服务器
    MYSQL * conn = mysql_real_connect(mysql, "localhost", "root", "123456", MY_DB, 0, NULL, 0);
    if(conn == NULL)
    {
            printf ("mysql_init error: %s\n", mysql_error(mysql));
            return NULL;
    }


    // 设置中文显示
    mysql_query(mysql, "set names utf8");
    printf ("连上my_db......\n");

    return mysql;
}

// 成功返回0， 失败返回-1
int mysql_exec(MYSQL *mysql,  const char * sql)
{
		//  mysql语句执行
    int ret = mysql_query(mysql, sql);
    if (ret != 0)
    {
            printf ("mysql_query error: %s\n", mysql_error(mysql));
            return -1;
    }

    // 从服务器下载数据到本地
    //mysql_store_result()将查询的全部结果读取到客户端，分配1个MYSQL_RES结构，并将结果置于该结构中。
    MYSQL_RES *mysql_res = mysql_store_result(mysql);
    if (mysql_res == NULL)
    {
            // 并没有发生错误，只是没有取到值而已
            if (mysql_errno(mysql) == 0)
            {
                    printf ("Query OK!\n");
                    return 0;
            }
            else
            {
                    printf ("mysql_store_result error: %s\n", mysql_error(mysql));
                    return -1;
            }
    }

    // 获取列数
    unsigned int num_fields =  mysql_num_fields(mysql_res);

    // 获取每一列的字段
    //返回所有MYSQL_FIELD结构的数组。每个结构提供了结果集中1列的字段定义。
    MYSQL_FIELD *field = mysql_fetch_fields(mysql_res);
    int i = 0;
    for (i = 0; i < num_fields; i++)
    {
            printf ("%-8s", field[i].name);
    }
    printf ("\n");

    MYSQL_ROW row;
    // 一行一行处理数据
    //下一行的MYSQL_ROW结构。如果没有更多要检索的行或出现了错误，返回NULL。
    while(row = mysql_fetch_row(mysql_res))
    {
            // printf ("%s  %s  %s  %s  %s\n", row[0], row[1], row[2], row[3], row[4]);

            for (i = 0; i < num_fields; i++)
            {
                    printf ("%-8s", row[i]);
            }
            printf ("\n");
    }
    mysql_free_result(mysql_res);

    return 0;
}

int main()
{
	
    MYSQL *mysql = init();
    if (mysql == NULL)
    {
        return -1;
    }

    printf ("Welcome to the MySQL monitor\n");
    char buf[1024];
    while (1)
    {
        printf ("\nmysql> ");

        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);

        if (0 == strncmp(buf, "exit", 4) || 0 == strncmp(buf, "quit", 4))
        {
                break;
        }

        int ret = mysql_exec(mysql, buf);
        if (ret != 0 )
        {
                return -1;
        }
    }


    mysql_close(mysql);
    return 0;
}


#if 0
char** func()
{
    char **arr = (char **)malloc(sizeof(char*) * 10);
    
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		arr[i] = (char *)malloc(sizeof(char)*100);
	}

	return arr;
}

int main()
{
	char **buf = func();
	
	strcpy(buf[0], "hello");
	strcpy(buf[1], "world");
	
	printf ("%s %s\n", buf[0], buf[1]);
    return 0;	
}

#endif








