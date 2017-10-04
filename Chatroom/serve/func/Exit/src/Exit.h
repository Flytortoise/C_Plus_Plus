#ifndef EXIT_H_
#define EXIT_H_

#include "Abstract.h"

class Exit : public AB_Function
{
public :
	int Function(int client_stock);
	static Exit * GetExit();
	static void FreeExit();
	static Exit * Exit_;

private :
	Exit();

};



#endif

