#ifndef MY_SCANF
#define MY_SCANF

#include "Abstract.h"

class AB_Scanf :public AB_Action
{
public :
	virtual int Action(char s[], int len);
};

class MyScanf : public AB_Scanf
{

public :
	static MyScanf * scanf_;
	static MyScanf * GetScanf();
	static void FreeScanf();
	int Action();
	int Action(int t);
	int Action(char s[], int len);
	void me_scanf(char *str);
	char my_getchar();

private :
	MyScanf();

};

#endif
