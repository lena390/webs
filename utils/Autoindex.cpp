/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:47:27 by atable            #+#    #+#             */
/*   Updated: 2021/07/08 16:06:24 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers.hpp"

std::string autoindex( std::string path, std::string host, int port)
{
    std::stringstream response_body;
    std::stringstream res;
    std::string dirName(path);
	DIR *dir = opendir(path.c_str());
	response_body << "<!DOCTYPE html>\n<html>\n<head>\n<title>" + dirName + "</title>\n</head>\n<body>\n<h1>INDEX</h1>\n<p>\n";
	if (dir == NULL)
	{
		std::cout << RED << "ERROR" << RESET << std::endl;
		return "";
	}
	for(struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir))
	{
        if (dirEntry->d_name[0] != '.')
		    response_body << "\t\t<p><a href=" + dirName + "/"
                << std::string(dirEntry->d_name) << "\">" << std::string(dirEntry->d_name) << "</a></p>\n";
	}
	response_body << "</p>\n</body>\n</html>\n";
	res << "HTTP/1.1 200 OK\r\n" << "Version: HTTP/1.1\r\n" << "Content-Type: text/html; charset=utf-8\r\n" << "Content-Length: "
	<< response_body.str().length() << "\r\n\r\n" << response_body.str();
	closedir(dir);
    return res.str().c_str();
}