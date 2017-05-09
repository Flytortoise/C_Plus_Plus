#ifndef INTERFACE
#define INTERFACE

#include "Abstract.h"

using namespace std;

class Interface : AB_Action
{

static Interface *interface_;
static Interface * GetInterface();
static void FreeInterface();

public :
	void Action_pass();
	void Action(char *);
	void Action2(char *);
private :
	Interface();

};


#endif
