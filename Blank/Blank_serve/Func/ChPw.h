#ifndef CHPW_H_
#define CHPW_H_

#include "Abstract.h"
#include <mutex>

class ChPw : public AB_Function
{
public :
    int Function(int client_sock);
    static ChPw * GetChPw();
    static void FreeChPw();
    ~ChPw();
private :
    ChPw();
    static std::mutex _ChPw_lock;
    static ChPw * _ChPw;

    char *_idd;
    char *_passwd;
    char *_new_passwd;

    int DataBase();

};


#endif
