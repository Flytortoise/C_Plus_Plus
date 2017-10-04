#ifndef DEST_H_
#define DEST_H_

#include "Abstract.h"
#include <mutex>

class Dest : public AB_Function
{
public :
    int Function(int client_sock);
    static Dest * GetDest();
    static void FreeDest();
    ~Dest();
private :
    Dest();
    static std::mutex _Dest_lock;
    static Dest * _Dest;

    char *_idd;
    char *_passwd;

    int DataBase();
};


#endif
