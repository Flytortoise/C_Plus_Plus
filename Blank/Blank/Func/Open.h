#ifndef OPEN_H_
#define OPEN_H_


#include <mutex>

#include <string>
using namespace std;

class open_ask
{
public :
    void Init(char *name, char *id, char *passwd, char *money);
    void Func(char **outstr);

private:
    int _name_len;
    int _money_len;
    string _name;   //姓名
    string _id;     //身份证
    string _passwd; //密码
    string _money;  //存款金额

};


class Open
{
public :
    int Function(int client_sock, char *name, char *passwd, char *id, char *money);
    char *GetIdd();

    static Open * GetOpen();
    static void FreeOpen();

private :
    //Open(int sock, char *name, char *passwd, char *id, char *money);
    Open();
    static std::mutex _Open_lock;
    static Open * _Open;

    int _my_sock;   //
    open_ask _ask;  //请求信号

    int _result;    //应答结果
    char _idd[7];   //应答ID

};


#endif
