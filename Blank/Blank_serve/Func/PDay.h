#ifndef PDAY_H_
#define PDAY_H_

#include "Abstract.h"
#include <mutex>

class PDay : public AB_Function
{
public :
    int Function(int client_sock);
    static PDay * GetPDay();
    static void FreePDay();

private :
    PDay();
    static std::mutex _PDay_lock;
    static PDay * _PDay;
};


#endif
