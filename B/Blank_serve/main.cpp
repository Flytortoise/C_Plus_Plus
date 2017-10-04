#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include "Sock.h"

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }

    Sock sock(argv[1],atoi(argv[2]));
    sock.Work();

    return 0;
}

