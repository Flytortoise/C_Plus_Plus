#ifndef START_H_
#define START_H_

#include <vector>
#include <sqlite3.h>
#include "Abstract.h"

#define ACC_SIZE 20
#define PASS_SIZE 20
#define ID_SIZE 5
#define BUFF_SIZE 100
#define SEND_SIZE 100

typedef struct online
{
	int action;
    int sock;
	int flag;
	int chat_flag;
	int send_flag;
	int off_line;
	char id[ID_SIZE];
    char name[ACC_SIZE];
	char password[PASS_SIZE];
	char buffer[BUFF_SIZE];
	char send[SEND_SIZE];
}Node,*pNode;

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

	pNode user;

};



#endif 
