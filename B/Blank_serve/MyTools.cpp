#include "MyTools.h"

MyTools::MyTools(){}

int MyTools::DataHandle(vector<string>& temp)
{
    vector<string>::iterator t;
    for(t = temp.begin(); t != temp.end(); t++)
    {
        if(*t == "1")
        {
            return 1;
        }
    }

    return 0;
}
