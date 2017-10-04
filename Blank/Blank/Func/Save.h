#ifndef SAVE_H_
#define SAVE_H_


#include <mutex>

#include <string>
using namespace std;

class save_ask
{
public :
    void Init(char *idd, char *money);
    void Func(char **outstr);

private:
    int _idd_len;
    int _money_len;

    string _idd;
    string _money;
};


class Save
{
public :
    int Function(int client_sock, char *idd,char *money);
    static Save * GetSave();
    static void FreeSave();

private :
    Save();
    static std::mutex _Save_lock;
    static Save * _Save;

    save_ask _ask;  //请求信号
    int _result;    //应答信号
};


#endif
