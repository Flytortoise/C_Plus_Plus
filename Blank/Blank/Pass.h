#ifndef PASS_H_
#define PASS_H_

#include <string>

class pass_ask
{
public :
    pass_ask();
    void Init(char *name , char *passwd);
    void Func(char **outstr, int flag);
private:
    int _len;   //姓名的长度
    std::string _name;
    std::string _passwd;
};



class Pass
{
public:
    Pass(int client,char *name,char *passwd);
    int Action(int flag);

private:
    int client_sock;
    pass_ask _ask;  //请求信号
    int _reply;      //应答标志

};


#endif
