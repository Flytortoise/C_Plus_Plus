#ifndef FUNCFACTORY_H_
#define FUNCFACTORY_H_

#include "Abstract.h"
#include "Func/Func.h"

class pass : public AB_Factory
{
public :
	AB_Function * Factory();
};

class regi : public AB_Factory
{
public :
    AB_Function * Factory();
};

class open : public AB_Factory
{
public :
    AB_Function * Factory();
};

class save : public AB_Factory
{
public :
    AB_Function * Factory();
};

class draw : public AB_Factory
{
public :
    AB_Function * Factory();
};

class tran : public AB_Factory
{
public :
    AB_Function * Factory();
};

class inqu : public AB_Factory
{
public :
    AB_Function * Factory();
};

class chpw : public AB_Factory
{
public :
    AB_Function * Factory();
};


class hist : public AB_Factory
{
public :
    AB_Function * Factory();
};

class dest : public AB_Factory
{
public :
    AB_Function * Factory();
};



#endif

