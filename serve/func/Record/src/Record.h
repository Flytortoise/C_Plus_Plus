#ifndef RECORD_H_ 
#define RECORD_H_

#include "Abstract.h"

class Record : public AB_Function
{
	public :
	int Function(int client_stock);
	static Record * GetRecord();
	static void FreeRecord();
	static Record * Record_;

private :
	Record();

};



#endif

