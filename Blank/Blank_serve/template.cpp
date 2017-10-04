#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "Pass.h"

int Pass::Function(int client_sock)
{
    printf("Pass funccccc!!!!!!\n");
    return 0;
}

Pass * Pass::_Pass = NULL;
std::mutex Pass::_Pass_lock;

Pass * Pass::GetPass()
{
    std::unique_lock<std::mutex> lock(_Pass_lock);
    if(_Pass == NULL)
    {
        _Pass = new Pass();
    }

    return _Pass;
}
void Pass::FreePass()
{
    std::unique_lock<std::mutex> lock(_Pass_lock);
    if(_Pass != NULL)
    {
        delete _Pass;
        _Pass = NULL;
    }
}


Pass::Pass()
{

}
