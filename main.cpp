
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <libc.h>
#include <fstream>

char *string_to_char(std::string & s)
{
    char *str;

    str = new char[s.size() + 1];
    int i = 0;
    while (i < s.size()) {
        str[i] = s.at(i);
        i++;
    }
    str[i] = '\0';
    return str;
}

int main()
{
    struct sockaddr_in addr;
    socklen_t sizeofaddr;

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr *)&addr, sizeof addr);

    listen(sockfd, SOMAXCONN);

    int new_connection;
    while (1) {
        new_connection = accept(sockfd, (struct sockaddr *) &addr, &sizeofaddr);
        if (new_connection == 0)
            printf("Connection error\n");
        else {
            printf("Connected to client\n");
            const int request_buffer_size = 65536;
            char      request[request_buffer_size];

            int bytes_recvd = recv(new_connection, request, request_buffer_size - 1, 0);
            if (bytes_recvd < 0)
            {
                fprintf(stderr, "error recv\n");
                return 0;
            }
            request[bytes_recvd] = '\0';
            printf("request:\n%s\n",request);

            std::ifstream my_file("file", std::ios::in);
            std::string line;

            std::string buffer;
            buffer.append("HTTP/1.1 200 OK\n\n");
            while (getline(my_file, line))
            {
                buffer.append(line);
                buffer.append("\n");
            }

            char *buf = string_to_char(buffer);
            send(new_connection, buf, buffer.size(), 0);
            close(new_connection);
            delete(buf);
        }
    }
}