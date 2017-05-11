#ifndef DATA_H_
#define DATA_H_

#define ACC_SIZE 20
#define PASS_SIZE 20
#define ID_SIZE 5
#define BUFF_SIZE 100
#define SEND_SIZE 100

#include "Abstract.h"

class Online_data : public AB_Data		//通信的交互数据
{

public :
	Online_data();
	static Online_data * data;
	static Online_data* GetData();
	static void FreeData();

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
private :
	
	
};

typedef class Online_data Node;
typedef class Online_data pNode;


#endif
