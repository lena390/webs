/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:04:49 by atable            #+#    #+#             */
/*   Updated: 2021/07/06 14:16:07 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"
#include <errno.h>

CGI::CGI( void ) { return ; }

CGI::~CGI( void ) { return ; }

CGI::CGI( CGI const & cgi )
{
    this->_env = cgi._env;
}

CGI::CGI( Request_info * request, Inside & info )
{
    this->_body = request->getBody();
    std::map<std::string, std::string> tmp = request->getHeaders();
    if (tmp.find("Auth-Scheme") != tmp.end())
        this->_env["AUTH_TYPE"] = tmp["Authorization"];
    this->_env["CONTETNT_LENGTH"] = itoa(strlen(this->_body));
    this->_env["CONTENT_TYPE"] = tmp["Content-Type"];
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->_env["PATH_INFO"] = ""; //Костыль надо исправить
    this->_env["PATH_TRANSLATED"] = ""; //Костыль надо исправить
    this->_env["QUERY_STRING"] = ""; //Костыль надо исправить
    if (info.getListen().host == "")
        this->_env["REMOTE_ADDR"] = "127.0.0.1";
    else
        this->_env["REMOTE_ADDR"] = info.getListen().host;
    this->_env["REMOTE_IDENT"] = tmp["Authorization"];
    this->_env["REMOTE_USER"] = tmp["Authorization"];
    this->_env["SCRIPT_NAME"] = info.getCgiPass();
    this->_env["REDIRECT_STATUS"] = "200";    
    if (tmp.find("Hostname") != tmp.end())
        this->_env["SERVER_NAME"] = tmp["Hostname"];
    else
        this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
    this->_env["SERVER_PORT"] = itoa(info.getListen().port);
    this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    this->_env["SERVER_SOFTWARE"] = "Webserv/1.0";
    this->_env["REQUEST_METHOD"] = request->getMethod();
    this->_env["REQUEST_URI"] = ""; //Костыль!!!
}

char **CGI::to_array( void )
{
    char **arr;
    int i = 0;

    arr = new char*[this->_env.size() + 1];
    for (std::map<std::string, std::string>::iterator it = this->_env.begin();
            it != this->_env.end(); it++)
    {
        int size = it->first.length() + it->second.length();
        std::string tmp = it->first + " " + it->second;
        arr[i] = new char[size + 1];
        for (int j = 0; j < size; j++)
            arr[i][j] = tmp[j];
        i++;
    }
    arr[i] = NULL;
    return arr;
}

void CGI::clearEnvArr( char **arr )
{
    for (int i = 0; arr[i] != NULL; i++)
        delete [] arr[i];
    delete [] arr;
}

std::string CGI::startCGI( const std::string & filename )
{
    int in, out;
    std::string newStr = "";
    char **env_arr = this->to_array();

    FILE *infile = tmpfile();
    FILE *outfile = tmpfile();
    in = fileno(infile);
    out = fileno(outfile);
    
    write(in, this->_body, strlen(this->_body));
    lseek(in, 0, SEEK_SET);
    
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        std::cerr << RED << "CGI ERROR" << RESET << std::endl;
        return "error 505";
    }
    else if (pid == 0)
    {
        char *arr[2] = { const_cast<char*>(filename.c_str()), NULL };
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        execve(filename.c_str(), arr, env_arr);
        std::cerr << RED << "Execve error" << RESET << std::endl;
        write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
    }
    else
    {
        waitpid(-1, NULL, 0);
        lseek(out, 0, SEEK_SET);
        char buf[65523];
        int ret = 1;
        while (ret > 0)
        {
            memset(buf, 0, 65523);
            ret = read(out, buf, 65522);
            newStr += buf;
        }
    }

    fclose(infile);
    fclose(outfile);
    close(in);
    close(out);

    this->clearEnvArr(env_arr);

    if (!pid)
        exit(0);
    
    return newStr;
}