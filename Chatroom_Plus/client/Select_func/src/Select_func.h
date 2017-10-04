#ifndef SELECT_FUNC
#define SELECT_FUNC

#include "Abstract.h"

class Select_Direct : public AB_Director
{
public :
	int Direct();
	int Direct(int t);
	virtual int Direct(int t, int *, char *);
	virtual int Direct2(int t, int *, char *);
};

class Select : public Select_Direct
{
public :
	int Direct(int t,int *,char *);
	int Direct2(int t,int *,char *);
	static Select *select_ ;
	static Select * GetSelect();
	static void FreeSelect();

private :
	Select();
	AB_Function * Func;
	AB_Factory * Fact;

	int Check(char *);
};

#endif
