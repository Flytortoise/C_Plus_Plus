#include "Exit.h"
#include "Data.h"
#include "Start.h"
#include "main.h"
int Exit::Function(int client_sock)
{
	vector<Node>::iterator t = OnlinePeople.begin();
	while(t != OnlinePeople.end())
	{
		if(t->sock == client_sock)
		{
			t = OnlinePeople.erase(t);			
		}
		else
		{
			t++;
		}	
		
	}
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

