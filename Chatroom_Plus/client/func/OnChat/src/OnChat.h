#ifndef ONCHAT_H_ 
#define ONCHAT_H_

#include "Abstract.h"
#include "my_scanf.h"

class OnChat : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static OnChat * GetOnChat();
	static void FreeOnChat();
	static OnChat * OnChat_;
private :
	OnChat();
	MyScanf * scan;
};



#endif

