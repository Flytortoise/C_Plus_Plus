#ifndef HIST_H_
#define HIST_H_

#include "Abstract.h"
#include <mutex>
#include <string>
#include <vector>
using namespace std;

class Hist : public AB_Function
{
public :
    int Function(int client_sock);
    static Hist * GetHist();
    static void FreeHist();
    ~Hist();
private :
    Hist();
    static std::mutex _Hist_lock;
    static Hist * _Hist;

    char *_idd;
    char *_passwd;
    char *_str1;
    char *_str2;

    int DataBase();

    vector<string> _information;
    string _LineInformation;
};


#endif
