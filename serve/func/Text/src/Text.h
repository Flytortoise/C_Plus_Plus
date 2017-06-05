#ifndef TEXT_H_ 
#define TEXT_H_

#include "Abstract.h"

class Text : public AB_Function
{
	public :
	int Function(int client_stock);
	static Text * GetText();
	static void FreeText();
	static Text * Text_;

private :
	Text();

};



#endif

