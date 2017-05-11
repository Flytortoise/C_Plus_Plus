#ifndef START_H_
#define START_H_

#include <vector>
#include <sqlite3.h>
#include "Abstract.h"
#include "Pass.h"
#include "Select_func.h"
#include "Data.h"

using namespace std;

class start : public AB_Director
{
public :
	static start * CreateStart();
	static void FreeStart();
	static start * my_start_;
	int Direct(int client_stock);

	static vector <Online_data> OnlinePeople;

private :
	start();
	void Date_base(int client_stock);
	//int OffLine(void *para, int count, char **c_value, char **c_name);

	char *etc2_;
	char *msg_;
	sqlite3 *db2_;

	Online_data *user;



	AB_Action *pass;
	Select_Direct *select;
};



#endif 

