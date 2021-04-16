#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct strct
{
    int is_correct;
} bigass_struct;

void parse_config_file(bigass_struct &);
int  launch_server(bigass_struct &, struct sockaddr_in &);
//void process_request(bigass_struct &, struct sockaddr_in &, int &) { std::cout << "puk\n"; exit(0);}
void init_info_struct(bigass_struct &);
void process_request(bigass_struct & bas, struct sockaddr_in & addr, int sockfd);
