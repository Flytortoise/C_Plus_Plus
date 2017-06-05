#ifndef FACE_H_
#define FACE_H_

#include "Abstract.h"
#include "my_scanf.h"

class Face : public AB_Function
{
public :
	int Function(int client_stock);
	int Function();
	static Face * GetFace();
	static void FreeFace();
	static Face * Face_;
private :
	Face();
	MyScanf * scan;
};



#endif

