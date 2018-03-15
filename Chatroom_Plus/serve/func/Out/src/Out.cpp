#include "Out.h"
#include "Data.h"
#include "Start.h"
#include "main.h"

int Out::Function(int client_sock)
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

	return -2;
}

Out * Out::Out_ = NULL;

Out * Out::GetOut()
{
	if(Out_ == NULL)
	{
		Out_ = new Out();
	}

	return Out_;
}
void Out::FreeOut()
{
	if(Out_ != NULL)
	{
		delete Out_;
		Out_ = NULL;
	}
}


Out::Out()
{

}

