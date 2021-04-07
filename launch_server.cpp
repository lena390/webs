#include "header.hpp"

int  launch_server(bigass_struct & bas, struct sockaddr_in & addr)
{
    socklen_t   sizeofaddr;
    int         sockfd;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr *)&addr, sizeof addr);

    listen(sockfd, SOMAXCONN);

    return sockfd;
}