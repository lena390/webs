/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:35:53 by atable            #+#    #+#             */
/*   Updated: 2021/07/07 18:07:50 by atable           ###   ########.fr       */
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
    if (txts.find(extension) == std::string::npos || file_name.find(".") == std::string::npos)
        return "application/octet-stream";
    else
        return "text/" + extension;
}

std::string Response::append_body(Request_info * request, std::string & respond, Inside & config) {
    char cwd[PATH_MAX];
    if (getcwd(cwd,  sizeof(cwd)) == NULL) {
        respond = append_message(respond, 500, (std::string &) "", request);
        return respond.append("\r\nInternal Error 500 get cwd\n");
    }
    std::string cwd_str(cwd);
    std::string root(config.getLocation().find(request->getTarget())->second.getRoot());
    std::string index(config.getLocation().find(request->getTarget())->second.getIndex()[1]);
    std::string fullAddr(cwd_str + "/" + root + "/" + index);
    std::ifstream file(fullAddr);
    if (file.is_open()) {
        respond.append("\r\n");
        std::string line;
        while (getline(file, line)) {
            respond.append(line);
            respond.append("\n");
        }
    }
    else {
        respond.append("could not append body");
    }
    file.close();
    respond.append("\r\n");
    return respond;
}

std::string Response::POST_respond(Request_info * request, std::string & respond, Inside & config) {
    if (config.getLocation().count(request->getTarget()) && config.getMethods().find(request->getMethod()) != config.getMethods().end()) //
    {
        if (request->getBody_size() > config.getClientBodySize())
            return respond.append("\r\nInternal Error 413 Request Entity Too Large\n");
        char cwd[PATH_MAX];
        if (getcwd(cwd,  sizeof(cwd)) == NULL) {
            respond = append_message(respond, 500, (std::string &) "", request);
            return respond.append("\r\nInternal Error 500 get cwd\n");
        }
        std::string cwd_string(cwd);
        std::string root(config.getLocation().find(request->getTarget())->second.getRoot());
        std::string index(config.getLocation().find(request->getTarget())->second.getIndex()[0]);
        std::ofstream myfile(cwd_string + "/" + root + "/" + index, std::fstream::out);
        if (myfile.is_open()) {
            myfile << request->getBody();
            myfile.close();
        }
        else {
            return respond.append("\r\nInternal Error 500 inside POST could not open file\n");
        }

        std::string stringOK("HTTP/1.1 201 CREATED\r\n");
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
    return "";
}

std::string Response::DELETE_respond(Request_info * request, std::string & respond, Inside & config) {
    if (config.getLocation().count(request->getTarget()) && config.getMethods().find(request->getMethod()) != config.getMethods().end()) //
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd,  sizeof(cwd)) == NULL) {
            respond = append_message(respond, 500, (std::string &) "", request);
            return respond.append("\r\nInternal Error 500 get cwd\n");
        }
        std::string cwd_string(cwd);
        std::string root(config.getLocation().find(request->getTarget())->second.getRoot());
        std::string index(config.getLocation().find(request->getTarget())->second.getIndex()[0]);
        std::remove((cwd_string + "/" + root + "/" + index).c_str());

        std::string stringOK("HTTP/1.1 200 OK\r\n");
        return respond = stringOK.append(respond);
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
    std::map<std::string, Inside> locationMap = config.getLocation();

    if (locationMap.count(request->getTarget()) && locationMap[request->getTarget()].getMethods().count(request->getMethod()))
    {
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

std::string Response::GET_respond(Request_info * request, std::string & respond, Inside & config)
{
    std::map<std::string, Inside> locationMap = config.getLocation();
    if (locationMap.count(request->getTarget()) && locationMap[request->getTarget()].getMethods().count(request->getMethod()))
        {
        char cwd[PATH_MAX];
        if (getcwd(cwd,  sizeof(cwd)) == NULL) {
            respond = append_message(respond, 500, (std::string &) "", request);
            return respond.append("\r\nInternal Error 500 get cwd\n");
        }
        std::string cwd_str(cwd);
        std::string root(config.getLocation().find(request->getTarget())->second.getRoot());
        std::string index(config.getLocation().find(request->getTarget())->second.getIndex()[1]);
        std::string fullAddr(cwd_str + "/" + root + "/" + index);
        std::ifstream is(fullAddr, std::ifstream::binary);

        int length;
        if (is.is_open()) {
            is.seekg (0, is.end);
            length = is.tellg();
            is.seekg (0, is.beg);
            is.close();
        }
        else {
            respond = append_message(respond, 500, (std::string &) "", request);
            return respond.append("\r\nInternal Error 500 ifstream open\n" + fullAddr + "\n");
        }
        respond.append("Content-Length: ");
        char *s = itoa(length);
        respond.append(s);
        free(s);
        respond.append("\r\n");

        respond.append("Content-Type: ");
        respond.append(get_content_type(request->getTarget() + ".html")); //
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
     if (request->getMethod() == "HEAD")
         respond = HEAD_respond(request, respond, config);
     else if (request->getMethod() == "GET")
        respond = GET_respond(request, respond, config);
     else if (request->getMethod() == "DELETE")
        respond = DELETE_respond(request, respond, config);
     else if (request->getMethod() == "POST")
         respond = POST_respond(request, respond, config);
     else {
        respond = append_message(respond, 501, request->getTarget(), request);
        respond.append("\r\n Not Implemented 501\n");
     }
     return respond;
}