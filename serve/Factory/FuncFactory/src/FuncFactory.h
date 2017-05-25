#ifndef FUNCFACTORY_H_
#define FUNCFACTORY_H_

#include "Abstract.h"

class look : public AB_Factory
{
public :
	AB_Function * Factory();
};

class chat : public AB_Factory
{
public :
	AB_Function * Factory();
};

class out : public AB_Factory
{
public :
	AB_Function * Factory();
};


#endif

