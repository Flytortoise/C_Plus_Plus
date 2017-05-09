#ifndef MY_SCANF
#define MY_SCANF

#include "Abstract.h"

class MyScanf : AB_Action
{

static MyScanf * scanf_;
static MyScanf * GetScanf();
static void FreeScanf();

public :
	int Action(char s[], int len);
	void me_scanf(char *str);
	char my_getchar();

private :
	MyScanf();

};

#endif
