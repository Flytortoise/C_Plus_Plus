#ifndef ALLCHAT_H_
#define ALLCHAT_H_

#include "Abstract.h"
#include "my_scanf.h"

class AllChat : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static AllChat * GetAllChat();
	static void FreeAllChat();
	static AllChat * AllChat_;
private :
	AllChat();
	MyScanf * scan;
};



#endif

