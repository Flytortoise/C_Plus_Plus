#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "PDay.h"

int PDay::Function(int client_sock)
{
    printf("PDay funccccc!!!!!!\n");
    return 0;
}

PDay * PDay::_PDay = NULL;
std::mutex PDay::_PDay_lock;

PDay * PDay::GetPDay()
{
    std::unique_lock<std::mutex> lock(_PDay_lock);
    if(_PDay == NULL)
    {
        _PDay = new PDay();
    }

    return _PDay;
}
void PDay::FreePDay()
{
    std::unique_lock<std::mutex> lock(_PDay_lock);
    if(_PDay != NULL)
    {
        delete _PDay;
        _PDay = NULL;
    }
}


PDay::PDay()
{

}
