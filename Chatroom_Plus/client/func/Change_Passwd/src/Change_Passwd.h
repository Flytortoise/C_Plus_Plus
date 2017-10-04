#ifndef CHANGE_PASSWD_H_
#define CHANGE_PASSWD_H_

#include "Abstract.h"
#include "my_scanf.h"

class Change_Passwd : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Change_Passwd * GetChange_Passwd();
	static void FreeChange_Passwd();
	static Change_Passwd * Change_Passwd_;
private :
	Change_Passwd();
	MyScanf * scan;
};



#endif

