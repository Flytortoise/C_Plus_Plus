#include "Abstract.h"


AB_Action::~AB_Action(){}
int AB_Action::Action(int t){ return 0; }
int AB_Action::Action(){ return 0; }

AB_Function::~AB_Function(){}
int AB_Function::Function(int t){ return 0; }
int AB_Function::Function(){ return 0; }


AB_Function * AB_Factory::Factory(){ return 0; }
AB_Factory::~AB_Factory(){}	
