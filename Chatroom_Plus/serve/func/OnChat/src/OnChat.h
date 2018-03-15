#ifndef ONCHAT_H_ 
#define ONCHAT_H_

#include "Abstract.h"

class OnChat : public AB_Function
{
	public :
	int Function(int client_stock);
	static OnChat * GetOnChat();
	static void FreeOnChat();
	static OnChat * OnChat_;

private :
	OnChat();

};



#endif

