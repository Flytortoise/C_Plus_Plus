#ifndef PHIS_H_
#define PHIS_H_

#include "Abstract.h"
#include <mutex>

class PHis : public AB_Function
{
public :
    int Function(int client_sock);
    static PHis * GetPHis();
    static void FreePHis();

private :
    PHis();
    static std::mutex _PHis_lock;
    static PHis * _PHis;
};


#endif
