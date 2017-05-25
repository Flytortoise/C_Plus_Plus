#include "FuncFactory.h"
#include "DynBase.h"
#include "Look.h"
#include "Chat.h"
#include "Exit.h"

REGISTER_CLASS(look);
REGISTER_CLASS(chat);
REGISTER_CLASS(out);

AB_Function * look::Factory()
{
	return Look::GetLook();
}

AB_Function * chat::Factory()
{
	return Chat::GetChat();
}

AB_Function * out::Factory()
{
	return Exit::GetExit();
}


