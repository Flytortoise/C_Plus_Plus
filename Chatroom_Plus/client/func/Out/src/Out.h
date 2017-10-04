#ifndef OUT_H_
#define OUT_H_

#include "Abstract.h"

class Out : public AB_Function
{
public :
	int Function(int client_stock);
	static Out * GetOut();
	static void FreeOut();
	static Out * Out_;

private :
	Out();

};



#endif

