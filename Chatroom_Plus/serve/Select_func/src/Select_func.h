#ifndef SELECT_FUNC
#define SELECT_FUNC

#include "Abstract.h"

using namespace std;

class Select_Direct : public AB_Director
{
public :
	virtual int Direct(int t, int *);
	virtual int Direct2(int t, int *);
};

class Select : public Select_Direct
{
public :
	static Select *select_ ;
	static Select * GetSelect();
	static void FreeSelect();
	virtual int Direct(int t, int *);
	virtual int Direct2(int t, int *);
private :
	Select();
	int Direct(int t);
	AB_Function * Func;
	AB_Factory * Fact;
};


#endif
