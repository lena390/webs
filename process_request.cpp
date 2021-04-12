#include "header.hpp"

void process_request(bigass_struct &bas, struct sockaddr_in &addr, int sockfd)
{
    socklen_t sizeofaddr;

    int new_connection = accept(sockfd, (struct sockaddr *)&addr, &sizeofaddr);
    if (new_connection == 0)
    {
        std::cout << "error accept()\n";
        return;
    }

    std::cout << "Connected to client\n";
    const int request_buffer_size = 65536;
    char request[request_buffer_size];

    int bytes_recvd = recv(new_connection, request, request_buffer_size - 1, 0);
    if (bytes_recvd < 0)
    {
        fprintf(stderr, "error recv()\n");
        return;
    }
    request[bytes_recvd] = '\0';

    //parse_request();
    //write_responce();
    //send_responce()

    std::cout << "request:\n" << request << std::endl;
    char buffer[256];
    strcat(buffer, "HTTP/1.1 200 OK\n\n");
    strcat(buffer, "Hello 1234");

    send(new_connection, buffer, strlen(buffer), 0);
    close(new_connection);
}