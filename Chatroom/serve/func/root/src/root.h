#ifndef ROOT_H_
#define ROOT_H_

#include "Abstract.h"

class Root : public AB_Function
{
public :
	virtual int Function(int client_stock);
	virtual int Function();
};



#endif