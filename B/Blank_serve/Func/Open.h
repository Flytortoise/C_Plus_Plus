#ifndef OPEN_H_
#define OPEN_H_

#include "Abstract.h"
#include <mutex>

class Open : public AB_Function
{
public :
    int Function(int client_sock);
    static Open * GetOpen();
    static void FreeOpen();
    ~Open();
private :
    Open();
    static std::mutex _Open_lock;
    static Open * _Open;

    char *_name;
    char *_passwd;
    char *_money;
    char *_id;

    int DataBase();

    char _idd[7];    //返回的ID号码
};


#endif
