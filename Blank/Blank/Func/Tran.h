#ifndef TRAN_H_
#define TRAN_H_


#include <mutex>
#include <string>

using namespace std;

class tran_ask
{
public :
    void Init(char *my_idd, char *passwd, char *money,char *other_idd);
    void Func(char **outstr);

private:
    int _my_idd_len;
    int _other_idd_len;
    int _money_len;

    string _my_idd;
    string _passwd;
    string _money;
    string _other_idd;

};

class Tran
{
public :
    int Function(int client_sock, char *my_idd,char *passwd, char *money, char *other_idd);
    static Tran * GetTran();
    static void FreeTran();

private :
    Tran();
    static std::mutex _Tran_lock;
    static Tran * _Tran;

    tran_ask _ask;
    int _result;

};


#endif
