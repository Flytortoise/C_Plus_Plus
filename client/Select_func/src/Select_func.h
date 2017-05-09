#ifndef SELECT_FUNC
#define SELECT_FUNC

#include "Abstartc.h"

class Select : public AB_Action
{

static Select *select_ ;
static Select * GetSelect();
static void FreeSelect();

public :
	int Action(int ,int *,char *);
	int Action2(int ,int *,char *);
private :
	Select();

};

#endif
