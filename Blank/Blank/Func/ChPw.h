#ifndef CHPW_H_
#define CHPW_H_

#include <mutex>

#include <string>
using namespace std;

class chpw_ask
{
public :
    void Init(char *idd, char *passwd, char *newpasswd);
    void Func(char **outstr);

private:
    int _idd_len;
    string _idd;     //帐号
    string _passwd; //密码
    string _new_passwd;

};



class ChPw
{
public :
    int Function(int client_sock,char *idd, char *passwd, char *newpasswd);
    static ChPw * GetChPw();
    static void FreeChPw();

private :
    ChPw();
    static std::mutex _ChPw_lock;
    static ChPw * _ChPw;

    chpw_ask _ask;
    int _result;



};


#endif
