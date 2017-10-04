#ifndef HELP_H_
#define HELP_H_

#include "Abstract.h"
#include "my_scanf.h"

class Help : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Help * GetHelp();
	static void FreeHelp();
	static Help * Help_;
private :
	Help();
	MyScanf * scan;
};



#endif

