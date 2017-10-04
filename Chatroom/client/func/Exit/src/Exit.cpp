#include "Exit.h"
#include "Data.h"
#include "Start.h"

int Exit::Function(int client_sock)
{
	return -1;
}

Exit * Exit::Exit_ = NULL;

Exit * Exit::GetExit()
{
	if(Exit_ == NULL)
	{
		Exit_ = new Exit();
	}

	return Exit_;
}
void Exit::FreeExit()
{
	if(Exit_ != NULL)
	{
		delete Exit_;
		Exit_ = NULL;
	}
}


Exit::Exit()
{

}

