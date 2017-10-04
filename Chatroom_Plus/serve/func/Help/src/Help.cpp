#include "Help.h"
#include "Data.h"
#include "Start.h"


int Help::Function(int client_sock)
{
	return 0;
}

Help * Help::Help_ = NULL;

Help * Help::GetHelp()
{
	if(Help_ == NULL)
	{
		Help_ = new Help();
	}

	return Help_;
}
void Help::FreeHelp()
{
	if(Help_ != NULL)
	{
		delete Help_;
		Help_ = NULL;
	}
}


Help::Help()
{

}

