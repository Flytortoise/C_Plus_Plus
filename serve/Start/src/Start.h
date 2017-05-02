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
	void Date_base();
	int OffLine(void *para, int count, char **c_value, char **c_name);

	char *etc2_;
	char *msg_;
	sqlite3 *db2_;
	pNode user;

	vector<Node> data;
};



#endif 
