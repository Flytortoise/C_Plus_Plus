#ifndef CHANGE_NAME_H_
#define CHANGE_NAME_H_

#include "Abstract.h"
#include "my_scanf.h"

class Change_Name : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Change_Name * GetChange_Name();
	static void FreeChange_Name();
	static Change_Name * Change_Name_;
private :
	Change_Name();
	MyScanf * scan;
};



#endif

