#ifndef ABSTRACT_H_
#define ABSTRACT_H_

class AB_Direct
{
public :
	virtual int Direct() = 0;
	virtual ~AB_Director();
}

class AB_Action
{
public :
	virtual int Action() = 0;
	virtual ~AB_Action();
}

class AB_Function
{
public :
	virtual int Function() = 0;
	virtual ~AB_Function();

}

class AB_Data
{
public :
	virtual int Data() = 0;
	virtual ~AB_Data();

}


#endif