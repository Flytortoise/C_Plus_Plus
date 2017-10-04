#ifndef HIST_H_
#define HIST_H_

#include <mutex>
#include <string>

using namespace std;

class hist_ask
{
public :
    void Init(char *_idd, char *passwd, char *str1,char *str2);
    void Func(char **outstr);

private:
    int _idd_len;
    int _str1_len;
    int _str2_len;

    string _idd;
    string _passwd;
    string _str1;
    string _str2;

};

class Hist
{
public :
    int Function(int client_sock, char *_idd,char *passwd, char *str1, char *str2);
    static Hist * GetHist();
    static void FreeHist();
    string GetInformation();
private :
    Hist();
    static std::mutex _Hist_lock;
    static Hist * _Hist;

    hist_ask _ask;
    int _result;

    void HandleInformation(int client_sock);

    string _information;

};



#endif
