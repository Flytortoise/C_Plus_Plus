#include "Out.h"
#include "Data.h"
#include "Start.h"

int Out::Function(int client_sock)
{
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

