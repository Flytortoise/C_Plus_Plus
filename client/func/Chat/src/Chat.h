#ifndef CHAT_H_
#define CHAT_H_

#include "Abstract.h"

class Chat : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Chat * GetChat();
	static void FreeChat();
	static Chat * chat_;
private :
	Chat();
	MyScanf * scan;
};



#endif

