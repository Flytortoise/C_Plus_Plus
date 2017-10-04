#ifndef ABSTRACT_H_
#define ABSTRACT_H_

class AB_Director
{
public :
	virtual int Direct(int t) = 0;
	virtual int Direct();
	virtual ~AB_Director();
};

class AB_Action
{
public :
	virtual int Action(int t) = 0;
	virtual int Action();
	virtual ~AB_Action();
};

class AB_Function
{
public :
	virtual int Function(int t) = 0;
	virtual int Function();
	virtual ~AB_Function();

};

class AB_Data
{
public :
	virtual ~AB_Data();

};

class AB_Factory
{
public :
	virtual AB_Function * Factory() = 0;
	virtual ~AB_Factory();	
};

#endif
