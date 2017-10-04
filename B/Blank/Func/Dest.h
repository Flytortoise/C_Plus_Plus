#ifndef DEST_H_
#define DEST_H_

#include <mutex>
#include <string>

using namespace std;

class dest_ask
{
public :
    void Init(char *_idd, char *passwd);
    void Func(char **outstr);

private :
    int _idd_len;

    string _idd;
    string _passwd;

};


class Dest
{
public :
    int Function(int client_sock, char *idd, char *passwd);
    static Dest * GetDest();
    static void FreeDest();

private :
    Dest();
    static std::mutex _Dest_lock;
    static Dest * _Dest;

    dest_ask _ask;
    int _result;
};


#endif
