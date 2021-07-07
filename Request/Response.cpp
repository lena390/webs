/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:35:53 by atable            #+#    #+#             */
/*   Updated: 2021/07/06 22:27:42 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "../parse/Inside.hpp"

Response::Response() { return ; }
Response::~Response() { return ; }

bool Response::CheckHTTPVersion(Request_info* request_info)
{
    if (request_info->getVersion() == "1.1")
        return true;
    else
        return false;
}

std::string Response::append_message(std::string & respond, int status_code, const std::string & location, Request_info * request) {
    std::string message;
    if (status_code == 400) { message = "HTTP/1.1 400 Bad Request"; }
    else if (status_code == 404) { message = "HTTP/1.1 404 Not Found"; }
    else if (status_code == 405) {
        message = "HTTP/1.1 405 Method Not Allowed";
        message.append("\r\nAllow: " + location);//
    }
    else if (status_code == 202) { message = "HTTP/1.1 202 Accepted"; }
    else if (status_code == 500) { message = "HTTP/1.1 500 Internal Server Error"; }
    else if (status_code == 501) { message = "HTTP/1.1 501 Not Implemented"; }
    else if (status_code == 505) { message = "HTTP/1.1 505 HTTP Version Not Supported"; }
    message.append("\r\n");
    message.append(respond);
    respond = message;
    return respond;
}

char * Response::get_file_modif_time(const char *path, char * buffer) {
    struct stat attr;
    struct tm * timeinfo;

    stat(path, &attr);
    timeinfo = gmtime(&attr.st_mtime);
    strftime(buffer, 38, "%a, %d %b %Y %T %Z", timeinfo);
    return buffer;
}

char * Response::get_formatted_date(char * buffer) {
    time_t now;
    struct tm * timeinfo;

    time(&now);
    timeinfo = gmtime(&now);
    strftime(buffer, 38, "%a, %d %b %Y %T %Z\r\n", timeinfo);
    return buffer;
}

std::string Response::get_content_type(const std::string file_name) {
    size_t pos = file_name.find_last_of('.');
    std::string extension = file_name.substr(pos + 1);
    if (extension == "htm") extension = "html";
    std::string txts = "css, csv, html, htm, ics, js, mjs, txt";
    if (txts.find(extension) < txts.length() || file_name.find(".") < file_name.length())
        return "text/" + extension;
    else
        return "application/octet-stream";
}

std::string Response::append_body(Request_info * request, std::string & respond, Inside & config) {
    //std::ifstream file("/home/lena/CLionProjects/Webs/" + config.locations);//config.locations.root
    std::ifstream file("/home/lena/CLionProjects/Webs/");//config.locations.root
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

std::string Response::POST_respond(Request_info * request, std::string & respond, Inside & config) {
    if (config.getLocation().count(request->getTarget()) && config.getMethods().find(request->getMethod()) != config.getMethods().end()) //
    {
        char* body = request->getBody();
        std::ofstream myfile;
        if (myfile.is_open()) {
            myfile.open(request->getTarget());
            myfile << request->getBody();
            myfile.close();
        }
        else {
            return respond.append("\r\nInternal Error 500 1\n");
        }

        Inside* test = new Inside();
//        config.getLocation()[request->getTarget()] = ;

        std::string stringOK("HTTP/1.1 201 OK\r\n");
        stringOK.append(respond);
        return respond = stringOK;
    }
    else if (config.getLocation().count(request->getTarget()))
    {
        respond = append_message(respond, 404, request->getTarget(), request);
        return respond.append("\r\n404 Not Found\n");
    }
    else if (config.getMethods().find(request->getMethod()) != config.getMethods().end())
    {
        respond = append_message(respond, 405, request->getTarget(), request);
        return respond.append("\r\n405 Method Not Allowed\n");
    }
    return "puk";
}

std::string Response::DELETE_respond(Request_info * request, std::string & respond, Inside & config) {
    if (config.getLocation().count(request->getTarget()) && config.getMethods().find(request->getMethod()) != config.getMethods().end()) //
    {
        config.getLocation().erase(request->getTarget());

        std::string stringOK("HTTP/1.1 200 OK\r\n");
        stringOK.append(respond);
        return respond = stringOK;
    }
    else if (config.getLocation().count(request->getTarget()))
    {
        respond = append_message(respond, 404, request->getTarget(), request);
        return respond.append("\r\n404 Not Found\n");
    }
    else if (config.getMethods().find(request->getMethod()) != config.getMethods().end())
    {
        respond = append_message(respond, 405, request->getTarget(), request);
        return respond.append("\r\n405 Method Not Allowed\n");
    }
    return NULL;
}


std::string Response::HEAD_respond(Request_info * request, std::string & respond, Inside & config)
{
    return NULL;
}
std::string Response::GET_respond(Request_info * request, std::string & respond, Inside & config)
{
    std::map<std::string, Inside> locationMap = config.getLocation();

    if (locationMap.count(request->getTarget()) && locationMap[request->getTarget()].getMethods().count(request->getMethod()))
//    if (locationMap.count(request->getTarget()) && locationMap[request->getTarget()].getMethods().find(request->getMethod()))

        {
//        std::ifstream is(request->getTarget(), std::ifstream::binary);
        std::ifstream is(request->getTarget(), std::ifstream::binary);
//        std::cout << request->getTarget() << "!!!!!!!!!\n";


        int length;
        if (is.is_open()) {
            is.seekg (0, is.end);
            length = is.tellg();
            is.seekg (0, is.beg);
            is.close();
        }
        else {
            std::cout << RED << "HERE" << RESET << std::endl;
            respond = append_message(respond, 500, (std::string &) "", request);
            return respond.append("\r\nInternal Error 500 2\n");
        }
        respond.append("Content-Length: ");
        char *s = itoa(length);
        respond.append(s);
        free(s);
        respond.append("\r\n");

        respond.append("Content-Type: ");
        respond.append(get_content_type(request->getTarget())); //
        respond.append("\r\n");

        char buffer[40];
        respond.append("Last-Modified: ");
        respond.append( get_file_modif_time(request->getTarget().c_str(), buffer)); //
        respond.append("\r\n");

        append_body(request, respond, config);

        std::string stringOK("HTTP/1.1 200 OK\r\n");
        stringOK.append(respond);

        return respond = stringOK;

    }
    else if (!locationMap.count(request->getTarget()))
    {
        respond = append_message(respond, 404, request->getTarget(), request);
        return respond.append("\r\n404 Not Found\nlocation " + request->getTarget() + " not found\n");
    }
    else if (!locationMap[request->getTarget()].getMethods().count(request->getMethod()))
    {
        respond = append_message(respond, 405, request->getTarget(), request);
        return respond.append("\r\n405 Method Not Allowed\n");
    }
    return "";
}

std::string Response::write_response(Request_info *request, Inside & config) {
    std::string respond;
    respond.append("Server: Puk(puk)\r\n");
    respond.append("Content-Language: en\r\n");
    char buffer[38];
    respond.append("Date: ");
    respond.append(get_formatted_date(buffer));

    std::map<std::string, Inside> locationMap = config.getLocation();
    std::vector<std::string> key;
    for(std::map<std::string, Inside>::iterator it = locationMap.begin(); it != locationMap.end(); ++it) {
        key.push_back(it->first);
        std::cout << "Key: " << it->first << std::endl;
    }


    if (!request->isCorrect()) {
        respond = append_message(respond, 400, request->getTarget(), request);
        return respond.append("\r\nBad Request 400\n");
    }
    if (!CheckHTTPVersion(request)) {
        respond = append_message(respond, 505, request->getTarget(), request);
        return respond.append("\r\nHTTP Version Not Supported 505\n");
    }
    // if (request->getMethod() == "HEAD")
    //     respond = HEAD_respond(request, respond, config);
    if (request->getMethod() == "GET")
        respond = GET_respond(request, respond, config);
    else {
        respond = append_message(respond, 501, request->getTarget(), request);
        respond.append("\r\n Not Implemented 501\n");
    }
    return respond;
}