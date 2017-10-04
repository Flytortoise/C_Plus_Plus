#ifndef SAVE_H_
#define SAVE_H_

#include "Abstract.h"
#include <mutex>

class Save : public AB_Function
{
public :
    int Function(int client_sock);
    static Save * GetSave();
    static void FreeSave();
    ~Save();
private :
    Save();
    static std::mutex _Save_lock;
    static Save * _Save;

    char *_idd;
    char *_money;

    int DataBase();
};


#endif
