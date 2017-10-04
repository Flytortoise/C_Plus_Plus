#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "PHis.h"

int PHis::Function(int client_sock)
{
    printf("PHis funccccc!!!!!!\n");
    return 0;
}

PHis * PHis::_PHis = NULL;
std::mutex PHis::_PHis_lock;

PHis * PHis::GetPHis()
{
    std::unique_lock<std::mutex> lock(_PHis_lock);
    if(_PHis == NULL)
    {
        _PHis = new PHis();
    }

    return _PHis;
}
void PHis::FreePHis()
{
    std::unique_lock<std::mutex> lock(_PHis_lock);
    if(_PHis != NULL)
    {
        delete _PHis;
        _PHis = NULL;
    }
}


PHis::PHis()
{

}
