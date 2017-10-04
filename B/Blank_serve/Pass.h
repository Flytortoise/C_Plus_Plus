#ifndef PASS_H_
#define PASS_H_

#include "Abstract.h"
#include <mutex>
#include <string>
#include <vector>
using namespace std;

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

    char *_name;
    char *_passwd;

    int DateBase(); //数据库处理
};


#endif
