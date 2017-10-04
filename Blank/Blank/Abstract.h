#ifndef ABSTRACT_H_
#define ABSTRACT_H_


class AB_Action
{
public :
    virtual int Action() ;
    virtual int Action(int t)= 0;
    virtual ~AB_Action();
};

class AB_Function
{
public :
    virtual int Function() ;
	virtual int Function(int t) = 0;
	virtual ~AB_Function();

};


class AB_Factory
{
public :
	virtual AB_Function * Factory() = 0;
	virtual ~AB_Factory();	
};

#endif
