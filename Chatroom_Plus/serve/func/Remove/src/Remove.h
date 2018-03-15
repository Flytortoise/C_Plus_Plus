#ifndef REMOVE_H_
#define REMOVE_H_

#include "Abstract.h"

class Remove : public AB_Function
{
	public :
	int Function(int client_stock);
	static Remove * GetRemove();
	static void FreeRemove();
	static Remove * Remove_;

private :
	Remove();

};



#endif

