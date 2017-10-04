#ifndef CHAT_H_
#define CHAT_H_

#include "Abstract.h"

class Chat : public AB_Function
{
	public :
	int Function(int client_stock);
	static Chat * GetChat();
	static void FreeChat();
	static Chat * Chat_;

private :
	Chat();

};



#endif

