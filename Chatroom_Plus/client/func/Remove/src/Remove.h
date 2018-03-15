#ifndef REMOVE_H_
#define REMOVE_H_

#include "Abstract.h"
#include "my_scanf.h"

class Remove : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Remove * GetRemove();
	static void FreeRemove();
	static Remove * Remove_;
private :
	Remove();
	MyScanf * scan;
};



#endif

