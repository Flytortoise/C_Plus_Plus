#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "my_scanf.h"

#include "Help.h"
#include "Start.h"

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
	scan = MyScanf::GetScanf();
}

int Help::Function(int client_sock)
{
    Interface::GetInterface()->Action(Online_data::GetData()->name);		//打印一次功能选择界面
}

int Help::Function() {}
