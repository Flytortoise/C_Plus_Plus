#include "FuncFactory.h"
#include "DynBase.h"


REGISTER_CLASS(save);
REGISTER_CLASS(draw);
REGISTER_CLASS(tran);
REGISTER_CLASS(inqu);
REGISTER_CLASS(chpw);
REGISTER_CLASS(pday);
REGISTER_CLASS(phis);
REGISTER_CLASS(hist);
REGISTER_CLASS(dest);




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

AB_Function * pday::Factory()
{
    return PDay::GetPDay();
}

AB_Function * phis::Factory()
{
    return PHis::GetPHis();
}

AB_Function * hist::Factory()
{
    return Hist::GetHist();
}

AB_Function * dest::Factory()
{
    return Dest::GetDest();
}





