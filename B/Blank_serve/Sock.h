#ifndef SOCK_H
#define SOCK_H

#include <Selectfunc.h>

struct fds
{
   int epollfd;
   int sockfd;
};

class Sock
{

public:
    Sock(char *ip, int port);
    void Work();
    static Selectfunc *_select; //有待优化
    static void reset_oneshot( int epollfd, int fd );
private:
    char *_ip;
    int _port;

    int setnonblocking( int fd );
    void addfd( int epollfd, int fd, bool oneshot );


    //void* worker( void* arg );

};

#endif // SOCK_H
