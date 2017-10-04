#ifndef INQU_H_
#define INQU_H_

#include "Abstract.h"
#include <mutex>
#include <string>

using namespace std;

class Inqu : public AB_Function
{
public :
    int Function(int client_sock);
    static Inqu * GetInqu();
    static void FreeInqu();
    ~Inqu();
private :
    Inqu();
    static std::mutex _Inqu_lock;
    static Inqu * _Inqu;

    char *_idd;
    char *_passwd;

    int DataBase();

    string _money;
};


#endif
