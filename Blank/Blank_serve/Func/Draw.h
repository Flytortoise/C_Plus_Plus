#ifndef DRAW_H_
#define DRAW_H_

#include "Abstract.h"
#include <mutex>

class Draw : public AB_Function
{
public :
    int Function(int client_sock);
    static Draw * GetDraw();
    static void FreeDraw();
    ~Draw();
private :
    Draw();
    static std::mutex _Draw_lock;
    static Draw * _Draw;

    char *_idd;
    char *_passwd;
    char *_money;

    int DataBase();

};


#endif
