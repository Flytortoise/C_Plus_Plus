#include "Record.h"
#include "Data.h"
#include "Start.h"
#include "main.h"


int Record::Function(int client_sock)
{
	return 0;
}

Record * Record::Record_ = NULL;

Record * Record::GetRecord()
{
	if(Record_ == NULL)
	{
		Record_ = new Record();
	}

	return Record_;
}
void Record::FreeRecord()
{
	if(Record_ != NULL)
	{
		delete Record_;
		Record_ = NULL;
	}
}


Record::Record()
{

}

