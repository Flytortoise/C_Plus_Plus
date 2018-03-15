#ifndef ALLCHAT_H_
#define ALLCHAT_H_

#include "Abstract.h"

class AllChat : public AB_Function
{
	public :
	int Function(int client_stock);
	static AllChat * GetAllChat();
	static void FreeAllChat();
	static AllChat * AllChat_;

private :
	AllChat();

};



#endif

