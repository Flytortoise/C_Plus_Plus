#ifndef HELP_H_
#define HELP_H_

#include "Abstract.h"

class Help : public AB_Function
{
	public :
	int Function(int client_stock);
	static Help * GetHelp();
	static void FreeHelp();
	static Help * Help_;

private :
	Help();

};



#endif

