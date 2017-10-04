#ifndef DRAW_H_
#define DRAW_H_


#include <mutex>

#include <string>

using namespace std;

class draw_ask
{
public :
    void Init(char *idd, char *passwd, char *money);
    void Func(char **outstr);

private:
    int _idd_len;
    int _money_len;

    string _idd;
    string _passwd;
    string _money;
};


class Draw
{
public :
    int Function(int client_sock, char *idd, char *passwd, char *money);
    static Draw * GetDraw();
    static void FreeDraw();

private :
    Draw();
    static std::mutex _Draw_lock;
    static Draw * _Draw;

    draw_ask _ask;
    int _result;
};


#endif
