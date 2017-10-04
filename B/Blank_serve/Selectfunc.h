#ifndef SELECTFUNC_H
#define SELECTFUNC_H

//单例模式

#include <mutex>

#include "Abstract.h"

class Selectfunc
{
public:
    static Selectfunc *GetSel();
    static void FreeSel();

    int Func(char *action, int client_sock);

private:
    Selectfunc();

    static std::mutex _sel_lock;
    static Selectfunc *_sel;

    AB_Factory * _Fact;

};

#endif // SELECTFUNC_H
