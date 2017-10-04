#ifndef PASS_H_
#define PASS_H_

#include "Abstract.h"
#include "Data.h"

class Pass : public AB_Action
{

public:
	int Action(int client_stock);

	static Pass * GetPass();
	static void FreePass();
	static Pass * pass_;
private:
	Pass();
	void Num2Str(int Num, char Str[]);
	//int Callback1(void *para, int count, char **c_value,char **c_name);	//检测有无信息
	//int Callback(void *para, int count, char **c_value,char **c_name);	//检测有无信息，并获取用户昵称
	//int Online_(char *);

	sqlite3 *db;	
	char *msg;		//数据库的返回信息
	char *etc;		//帐号密码数据库
	char buffer[BUFF_SIZE];		//缓存区
	int id_;		//随机生成的ID
	int stime;
	int online_flag;
	int id_flag;		//是否生成可用ID的标志位
	int select_flag;	//是否有查询结果的标志位


	Online_data *pass;		//返回的信息
};


#endif
