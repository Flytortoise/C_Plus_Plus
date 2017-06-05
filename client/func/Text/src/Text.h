#ifndef TEXT_H_ 
#define TEXT_H_

#include "Abstract.h"
#include "my_scanf.h"

class Text : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Text * GetText();
	static void FreeText();
	static Text * Text_;
private :
	Text();
	MyScanf * scan;
};



#endif

