#ifndef TRAN_H_
#define TRAN_H_

#include "Abstract.h"
#include <mutex>

class Tran : public AB_Function
{
public :
    int Function(int client_sock);
    static Tran * GetTran();
    static void FreeTran();
    ~Tran();
private :
    Tran();
    static std::mutex _Tran_lock;
    static Tran * _Tran;

    char *_my_idd;
    char *_other_idd;
    char *_passwd;
    char *_money;


    int DataBase();
};


#endif
