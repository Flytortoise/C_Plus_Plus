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

class allchat : public AB_Factory
{
public :
	AB_Function * Factory();
};

class fast : public AB_Factory
{
public :
	AB_Function * Factory();
};

class face : public AB_Factory
{
public :
	AB_Function * Factory();
};

class changename : public AB_Factory
{
public :
	AB_Function * Factory();
};

class changepasswd : public AB_Factory
{
public :
	AB_Function * Factory();
};
class help : public AB_Factory
{
public :
	AB_Function * Factory();
};

class out : public AB_Factory
{
public :
	AB_Function * Factory();
};

class text : public AB_Factory
{
public :
	AB_Function * Factory();
};

class ex : public AB_Factory
{
public :
	AB_Function * Factory();
};


#endif

