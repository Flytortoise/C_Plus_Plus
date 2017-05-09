#ifndef PASS_H_
#define PASS_H_

#include "Abstract.h"
#include "Data.h"

class Pass : public AB_Action
{

static Pass * pass_;
static Pass * GetPass();
static void FreePass();

public:
	AB_Data Action(int client_sock);
private:
	Pass();
	AB_Action * interface;
	AB_Action * my_scanf;	

	AB_Data *pass;		//返回的信息
};


#endif