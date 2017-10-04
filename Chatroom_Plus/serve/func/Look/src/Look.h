#ifndef LOOK_H_
#define LOOK_H_

#include "Abstract.h"

class Look : public AB_Function
{
	public :
	int Function(int client_stock);
	static Look * GetLook();
	static void FreeLook();
	static Look * look_;

private :
	Look();

};



#endif

