#ifndef INTERFACE
#define INTERFACE

#include "Abstract.h"

using namespace std;

class AB_Interface : public AB_Action
{
public :
	int Action();
	int Action(int t);
	virtual void Action_pass();
	virtual void Action(char *);
	virtual void Action2(char *);
};

class Interface : public AB_Interface
{
public :
	static Interface *interface_;
	static Interface * GetInterface();
	static void FreeInterface();
	void Action_pass();
	void Action(char *);
	void Action2(char *);
private :
	Interface();

};


#endif
