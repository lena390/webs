/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:04:49 by atable            #+#    #+#             */
/*   Updated: 2021/07/02 11:21:38 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI( void ) { return ; }

CGI::~CGI( void ) { return ; }

CGI::CGI( CGI const & cgi )
{
    this->_env = cgi._env;
}

CGI::CGI( Request_info * info, t_serv_config config)
{
    std::map<std::string, std::string> tmp = info->getHeaders();
    this->_env["CONTETNT_LENGTH"] = itoa(strlen(info->getBody()));
    this->_env["CONTENT_TYPE"] = tmp["Content-Type"];
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->_env["PATH_INFO"] = info->getTarget();
    this->_env["PATH_TRANSLATED"] = info->getTarget();
    this->_env["QUERY_STRING"];
    this->_env["REMOTE_ADDR"]; // Адрес будет получен из структуры в Insite
    this->_env["REMOTE_IDENT"] = tmp["Authorization"];
    this->_env["REMOTE_USER"] = tmp["Authorization"];
    this->_env["REQUEST_METHOD"] = info->getMethod();
    this->_env["SCRIPT_NAME"]; // Путь до файла с cgi скриптом
    this->_env["SERVER_NAME"]; // Также берем у Глеба
    this->_env["SERVER_PORT"]; // Взять из конфига
    this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    this->_env["SERVER_SOFTWARE"] = "Webserv/1.0";
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


/// ЖДЕМ НОРМАЛЬНЫЕ ИНВАЙРОМЕНТЫ
std::string CGI::startCGI( const std::string & filename, char **env)
{
    // STDIN = 0, STDOUT = 1
    int in, out;
    std::string newStr = "";

    FILE *infile = tmpfile();
    FILE *outfile = tmpfile();
    in = fileno(infile);
    out = fileno(outfile);
    
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        std::cout << RED << "CGI ERROR" << RESET << std::endl;
        return "error 505";
    }
    else if (pid == 0) // потомок
    {
        char *arr[2];
        arr[0] = new char(filename.length());
        strncpy(arr[0], filename.c_str(), filename.length());
        arr[1] = NULL;
        char * const * nll = NULL;

        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        execve(filename.c_str(), nll, env);
        // std::cout << "Child process done" << std::endl;
    }
    else    // родитель
    {
        waitpid(-1, NULL, 0);
        char buf[65523];
        int ret = 1;
        while (ret > 0)
        {
            memset(buf, 0, 65523);
            ret = read(out, buf, 65523);
            newStr += buf;
        }
        // std::cout << "This is parent" << std::endl;
    }
    fclose(infile);
    fclose(outfile);
    close(in);
    close(out);
    if (!pid)
        exit(0);
    return newStr;

}

// int main(int argc, char **argv, char **env)
// {
//     CGI cgi;
//     char **arr;
//     int i = 0;
//     while(env[i] != NULL)
//         i++;
//     arr = new char*[i];
//     int k;
//     for (int j = 0; j < i; j++)
//     {
//         k = 0;
//         while (env[j][k] != '\0')
//             k++;
//         arr[j] = new char[k];
//         strncpy(arr[j], env[j], k);
//     }
    
//     arr[i] = NULL;
//     std::cout << cgi.startCGI("cgi_test/cgi_test.py", arr) << std::endl;
//     return 0;
// }