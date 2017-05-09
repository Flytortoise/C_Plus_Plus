#ifndef START_H_
#define START_H_

#include <vector>
#include <sqlite3.h>
#include "Abstract.h"
#include "Data.h"
#include "Pass.h"
#include "Select_func.h"

class start : public AB_Director
{
public :
	static start * CreateStart();
	static void FreeStart();
	static start * my_start_;

	int Direct(int client_stock);

private :
	start();
	void *Son(void *p);
	void Data_base(int , Node &);
	void SendText(Node &)

	int fd[2];		//线程通信管道
	int move ;	//是否被踢出标志位，被踢出时为0
	int kong ;
	char id[ID_SIZE];
	pthread_t pid;	

	char etc[BUFF_SIZE];
	char buffer[BUFF_SIZE];
	time_t timep;
	char *time_save;
	char *msg;
	
	sqlite3 *db;

	AB_Data *user;

	AB_Action *pass;
	AB_Action *select;
	AB_Action * interface;

};



#endif 
