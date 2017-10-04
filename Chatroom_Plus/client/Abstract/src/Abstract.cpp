#include "Abstract.h"

AB_Director::~AB_Director(){}
int AB_Director::Direct(int t){}
int AB_Director::Direct(){}

AB_Action::~AB_Action(){}
int AB_Action::Action(int t){}
int AB_Action::Action(){}

AB_Function::~AB_Function(){}
int AB_Function::Function(int t){}
int AB_Function::Function(){}

AB_Data::~AB_Data(){}

AB_Function * AB_Factory::Factory(){}
AB_Factory::~AB_Factory(){}	
