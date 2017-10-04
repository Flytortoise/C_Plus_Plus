#include "Selectfunc.h"
#include <stdio.h>

#include "DynBase.h"
#include "FuncFactory.h"

std::mutex Selectfunc::_sel_lock;
Selectfunc *Selectfunc::_sel = NULL;

Selectfunc::Selectfunc(){}


int Selectfunc::Func(char *action , int client_sock)
{
   // printf("Selcet1!\n");
    _Fact = reinterpret_cast<AB_Factory *>(DynObjectFactory::CreateObject(action));
    //printf("Selcet2!\n");
    return _Fact->Factory()->Function(client_sock);

}



Selectfunc *Selectfunc::GetSel()
{
    std::unique_lock<std::mutex> lock(_sel_lock);
    if(_sel == NULL)
    {
        _sel = new Selectfunc;
    }

    return _sel;
}

void Selectfunc::FreeSel()
{
    std::unique_lock<std::mutex> lock(_sel_lock);

    if(_sel != NULL)
    {
        delete _sel;
        _sel = NULL;
    }
}



