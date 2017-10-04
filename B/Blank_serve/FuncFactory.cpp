#include "FuncFactory.h"
#include "DynBase.h"
#include "Pass.h"
#include "Regi.h"

REGISTER_CLASS(pass);
REGISTER_CLASS(regi);

REGISTER_CLASS(open);
REGISTER_CLASS(save);
REGISTER_CLASS(draw);
REGISTER_CLASS(tran);
REGISTER_CLASS(inqu);
REGISTER_CLASS(chpw);
REGISTER_CLASS(hist);
REGISTER_CLASS(dest);


AB_Function * pass::Factory()
{
    return Pass::GetPass();
}

AB_Function * regi::Factory()
{
    return Regi::GetRegi();
}



AB_Function * open::Factory()
{
    return Open::GetOpen();
}

AB_Function * save::Factory()
{
    return Save::GetSave();
}

AB_Function * draw::Factory()
{
    return Draw::GetDraw();
}

AB_Function * tran::Factory()
{
    return Tran::GetTran();
}

AB_Function * inqu::Factory()
{
    return Inqu::GetInqu();
}

AB_Function * chpw::Factory()
{
    return ChPw::GetChPw();
}


AB_Function * hist::Factory()
{
    return Hist::GetHist();
}

AB_Function * dest::Factory()
{
    return Dest::GetDest();
}
