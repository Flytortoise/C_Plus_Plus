#ifndef Fast_H_
#define Fast_H_

#include "Abstract.h"

class Fast : public AB_Function
{
	public :
	int Function(int client_stock);
	static Fast * GetFast();
	static void FreeFast();
	static Fast * Fast_;

private :
	Fast();

};



#endif

