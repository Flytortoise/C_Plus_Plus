#ifndef FAST_H_
#define FAST_H_

#include "Abstract.h"
#include "my_scanf.h"

class Fast : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Fast * GetFast();
	static void FreeFast();
	static Fast * Fast_;
private :
	Fast();
	MyScanf * scan;
};



#endif

