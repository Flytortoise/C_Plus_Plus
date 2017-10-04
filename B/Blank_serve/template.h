#ifndef PASS_H_
#define PASS_H_

#include "Abstract.h"
#include <mutex>

class Pass : public AB_Function
{
public :
    int Function(int client_sock);
    static Pass * GetPass();
    static void FreePass();

private :
    Pass();
    static std::mutex _Pass_lock;
    static Pass * _Pass;
};


#endif
