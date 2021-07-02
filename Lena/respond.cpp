#include "request_parser.hpp"
#include <ctime>
#include <map>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <cstring>

typedef struct structure {
    std::string locations = "hello.htm";
    std::string method = "GET";
} serv_config;



bool CheckHTTPVersion(Request_info* request_info)
{
    if (request_info->getVersion() == "1.1")
        return true;
    else
        return false;
}

std::string append_message(std::string & respond, int status_code, std::string & location, Request_info * request) {
    std::string message;
    if (status_code == 400) { message = "HTTP/1.1 400 Bad Request"; }
    else if (status_code == 404) { message = "HTTP/1.1 404 Not Found"; }
    else if (status_code == 405) {
        message = "HTTP/1.1 405 Method Not Allowed";
        message.append("\r\nAllow: " + location);//
    }
    else if (status_code == 500) { message = "HTTP/1.1 500 Internal Server Error"; }
    else if (status_code == 501) { message = "HTTP/1.1 501 Not Implemented"; }
    else if (status_code == 505) { message = "HTTP/1.1 505 HTTP Version Not Supported"; }
    message.append("\r\n");
    message.append(respond);
    respond = message;
    return respond;
}


char * get_file_modif_time(char *path, char * buffer) {
    struct stat attr;
    struct tm * timeinfo;

    stat(path, &attr);
    timeinfo = gmtime(&attr.st_mtime);
    strftime(buffer, 38, "%a, %d %b %Y %T %Z", timeinfo);
    return buffer;
}

char * get_formatted_date(char * buffer) {
    time_t now;
    struct tm * timeinfo;

    time(&now);
    timeinfo = gmtime(&now);
    strftime(buffer, 38, "%a, %d %b %Y %T %Z\r\n", timeinfo);
    return buffer;
}

std::string get_content_type(const std::string file_name) {
    size_t pos = file_name.find_last_of('.');
    std::string extension = file_name.substr(pos + 1);
    if (extension == "htm") extension = "html";
    std::string txts = "css, csv, html, htm, ics, js, mjs, txt";
    if (txts.find(extension) < txts.length() || file_name.find(".") < file_name.length())
        return "text/" + extension;
    else
        return "application/octet-stream";
}

char * itoa(int d) {
    int length = 0;
    int copy = d;
    while (copy) {
        length++;
        copy = copy / 10;
    }
    if (length == 0)
        return strdup("0");
    char str[length + 1];
    str[length] = '\0';
    int i = length - 1;
    while (d) {
        int j = d % 10;
        d = d / 10;
        str[i--] = j + 48;
    }
    return strdup(str);
}
std::string append_body(Request_info * request, std::string & respond, serv_config & config) {
    std::ifstream file("respond.cpp");//config.locations.root
    if (file.is_open()) {
        respond.append("\r\n");
        std::string line;
        while (getline(file, line)) {
            respond.append(line);
            respond.append("\n");
        }
    }
    file.close();
    respond.append("\r\n");
    return respond;
}

std::string HEAD_respond(Request_info * request, std::string & respond, serv_config & config) {
    if (request->getTarget() == config.locations && request->getMethod() == config.method)
    {
        respond.append("Content-Language: en\n");
        std::string stringOK("HTTP/1/1 200 OK\n");
        stringOK.append(respond);
        return stringOK;
    }
    else if (request->getTarget() != config.locations)
    {
        return append_message(respond, 404, config.locations, request);//not found
    }
    else if (request->getMethod() != config.method)
    {
        return append_message(respond, 405, config.locations, request);//Method Not Allowed
    }
}

std::string GET_respond(Request_info * request, std::string & respond, serv_config & config)
{
    if (request->getTarget() == config.locations && request->getMethod() == config.method) //
    {
        std::ifstream is("respond.cpp", std::ifstream::binary);
        int length;
        if (is) {
            is.seekg (0, is.end);
            length = is.tellg();
            is.seekg (0, is.beg);
            is.close();
        }
        else {
            respond = append_message(respond, 500, (std::string &) "", request);
            return respond.append("\r\nInternal Error 500\n");
        }
        respond.append("Content-Length: ");
        char *s = itoa(length);
        respond.append(s);
        free(s);
        respond.append("\r\n");

        respond.append("Content-Type: ");
        respond.append(get_content_type("respond.cpp")); //
        respond.append("\r\n");

        char buffer[40];
        respond.append("Last-Modified: ");
        respond.append( get_file_modif_time("respond.cpp" , buffer)); //
        respond.append("\r\n");

        append_body(request, respond, config);

        std::string stringOK("HTTP/1.1 200 OK\r\n");
        stringOK.append(respond);

        return respond = stringOK;

    }
    else if (request->getTarget() != config.locations)
    {
        respond = append_message(respond, 404, config.locations, request);
        return respond.append("\r\n404 Not Found\n");
    }
    else if (request->getMethod() != config.method)
    {
        respond = append_message(respond, 405, config.locations, request);
        return respond.append("\r\n405 Method Not Allowed\n");
    }
}

std::string POST {};

char * string_to_char(std::string & str) {
    char respond[str.length()];
    for (int i = 0; i < str.length(); i++) {
        respond[i] = str.at(i);
    }
    return respond;
}
std::string write_response(Request_info *request, serv_config & config) {
    std::string respond;
    respond.append("Server: Puk(puk)\r\n");
    respond.append("Content-Language: en\r\n");
    char buffer[38];
    respond.append("Date: ");
    respond.append(get_formatted_date(buffer));

    if (!request->isCorrect()) {
        respond = append_message(respond, 400, config.locations, request);
        return respond.append("\r\nBad Request 400\n");
    }
    if (!CheckHTTPVersion(request)) {
        respond = append_message(respond, 505, config.locations, request);
        return respond.append("\r\nHTTP Version Not Supported 505\n");
    }

    if (request->getMethod() == "HEAD")
        respond = HEAD_respond(request, respond, config);
    else if (request->getMethod() == "GET")
        respond = GET_respond(request, respond, config);
    else {
        respond = append_message(respond, 501, config.locations, request);
        respond.append("\r\n Not Implemented 501\n");
    }


    return respond;
}

int main() {
    char request[] = "GET / HTTP/1.1\r\n"
                     "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                     "Host: www.example.com\r\n"
                     "Accept-Language: ru-ru\r\n"
                     "Accept-Encoding: gzip, deflate\r\n"
                     "Connection: Keep-Alive\r\n\n";

    Request_info *ri = new Request_info(request);
    serv_config bas;
    std::string s = write_response(ri, bas);
    std::cout << s;
}