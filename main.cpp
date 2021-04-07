
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <libc.h>
#include <fstream>


int maffin()
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

            char buffer[256];
            strcat(buffer, "HTTP/1.1 200 OK\n\n");
          //  strcat(buffer, "<h1>");
            strcat(buffer, "Hello 1234");
          //  strcat(buffer, "</h1>");

            send(new_connection, buffer, strlen(buffer), 0);
            close(new_connection);
        }
    }
}