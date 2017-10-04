#ifndef REGI_H
#define REGI_H

#include "Abstract.h"
#include <mutex>

class Regi : public AB_Function
{
public :
    int Function(int client_sock);
    static Regi * GetRegi();
    static void FreeRegi();

private :
    Regi();
    static std::mutex _Regi_lock;
    static Regi * _Regi;

    char *_name;
    char *_passwd;
    int DateBase();
};

#endif // REGI_H
