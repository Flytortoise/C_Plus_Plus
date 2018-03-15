#ifndef OFFCHAT_H_
#define OFFCHAT_H_

#include "Abstract.h"

class OffChat : public AB_Function
{
	public :
	int Function(int client_stock);
	static OffChat * GetOffChat();
	static void FreeOffChat();
	static OffChat * OffChat_;

private :
	OffChat();

};



#endif

