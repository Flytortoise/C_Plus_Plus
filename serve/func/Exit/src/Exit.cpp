#include "Exit.h"
#include "Data.h"
#include "Start.h"

int Exit::Function(int client_sock)
{
	vector<Node>::iterator t = start::OnlinePeople.begin();
	while(t != start::OnlinePeople.end())
	{
		if(t->sock == client_sock)
		{
			t = start::OnlinePeople.erase(t);			
		}
		else
		{
			t++;
		}
		
	}

	start::flag = 0; 
	return 0;
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

