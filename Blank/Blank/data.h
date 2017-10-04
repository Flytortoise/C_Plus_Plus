#ifndef DATA
#define DATA

class AB_ask
{
public :
    virtual ~AB_ask();
    virtual int Func() = 0;
};

class AB_reply
{
public :
    virtual ~AB_reply();
    virtual int Func() = 0;
};


#endif // DATA

