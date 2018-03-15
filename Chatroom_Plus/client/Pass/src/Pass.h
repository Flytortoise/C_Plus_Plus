#ifndef PASS_H_
#define PASS_H_

#include "Abstract.h"
#include "interface.h"
#include "Data.h"
#include "my_scanf.h"

class Pass : public AB_Action
{

public:
	static Pass * pass_;
	static Pass * GetPass();
	static void FreePass();
	int Action();
	int Action(int client_sock);
private:
	Pass();
	AB_Interface * interface;
	AB_Scanf * my_scanf;	

	Online_data *pass;		//返回的信息
};


#endif
