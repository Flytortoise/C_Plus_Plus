#ifndef INQU_H_
#define INQU_H_


#include <mutex>


#include <string>

using namespace std;

class inqu_ask
{
public :
    void Init(char *idd, char *passwd);
    void Func(char **outstr);

private:
    int _idd_len;

    string _idd;
    string _passwd;
};



class Inqu
{
public :
    int Function(int client_sock, char *idd,char *passwd);
    static Inqu * GetInqu();
    static void FreeInqu();
    char *GetMoney();
    ~Inqu();
private :
    Inqu();
    static std::mutex _Inqu_lock;
    static Inqu * _Inqu;

    inqu_ask  _ask;
    int _result;

    char *_money;
};


#endif
