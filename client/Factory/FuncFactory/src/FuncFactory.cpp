#include "FuncFactory.h"
#include "DynBase.h"
#include "Look.h"
#include "Chat.h"
#include "AllChat.h"
#include "Fast.h"
#include "Face.h"
#include "Change_Name.h"
#include "Change_Passwd.h"
#include "Help.h"
#include "Out.h"
#include "Text.h"
#include "Exit.h"

REGISTER_CLASS(look);
REGISTER_CLASS(chat);
REGISTER_CLASS(allchat);
REGISTER_CLASS(fast);
REGISTER_CLASS(face);
REGISTER_CLASS(out);
REGISTER_CLASS(changename);
REGISTER_CLASS(changepasswd);
REGISTER_CLASS(help);
REGISTER_CLASS(text);
REGISTER_CLASS(ex);


AB_Function * look::Factory()
{
	return Look::GetLook();
}

AB_Function * chat::Factory()
{
	return Chat::GetChat();
}

AB_Function * allchat::Factory()
{
	return AllChat::GetAllChat();
}

AB_Function * fast::Factory()
{
	return Fast::GetFast();
}

AB_Function * face::Factory()
{
	return Face::GetFace();
}

AB_Function * changename::Factory()
{
	return Change_Name::GetChange_Name();
}

AB_Function * changepasswd::Factory()
{
	return Change_Passwd::GetChange_Passwd();
}

AB_Function * out::Factory()
{
	return Out::GetOut();
}

AB_Function * help::Factory()
{
	return Help::GetHelp();
}

AB_Function * text::Factory()
{
	return Text::GetText();
}

AB_Function * ex::Factory()
{
	return Exit::GetExit();
}


