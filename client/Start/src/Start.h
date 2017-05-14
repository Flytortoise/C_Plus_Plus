#ifndef START_H_
#define START_H_

#include <vector>
#include <sqlite3.h>
#include "Abstract.h"
#include "Data.h"
#include "Pass.h"
#include "Select_func.h"

extern int fd[2];		//线程通信管道
extern char id[ID_SIZE];

class start : public AB_Director
{
public :
	static start * CreateStart();
	static void FreeStart();
	static start * my_start_;
	static sqlite3 *db;

	

	int Direct();
	int Direct(int client_stock);

private :
	start();
	//void *Son(void *p);
	//void Data_base(int , Node &);
	//void SendText(Node &);
	
	Online_data *user;

	AB_Action *pass;
	Select_Direct *select;
	AB_Interface * interface;

};



#endif 
