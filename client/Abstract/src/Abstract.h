#ifndef ABSTRACT_H_
#define ABSTRACT_H_

class AB_Director
{
public :
	virtual int Direct() = 0;
	virtual int Direct(int t);
	virtual ~AB_Director();
};

class AB_Action
{
public :
	virtual int Action() = 0;
	virtual int Action(int t);
	virtual ~AB_Action();
};

class AB_Function
{
public :
	virtual int Function() = 0;
	virtual int Function(int t);
	virtual ~AB_Function();

};

class AB_Data
{
public :
	virtual ~AB_Data();

};

#endif
