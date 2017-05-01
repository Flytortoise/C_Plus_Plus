#ifndef START_H_
#define START_H_

#include <sqlite3.h>

void * Start(void *);

class start
{
public :
	static start * CreateStart();
	static void FreeStart();
	static start * my_start;
private :
	char *etc2;
	char *msg;
	sqlite3 *db2;


	start();
};

#endif 
