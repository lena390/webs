/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:04:49 by atable            #+#    #+#             */
/*   Updated: 2021/06/19 14:06:04 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI( void ) { return ; }

CGI::~CGI( void ) { return ; }

CGI::CGI( CGI const & cgi )
{
    this->env = cgi.env;
}

CGI::CGI( Request_info * info, t_serv_config config)
{
    std::map<std::string, std::string> tmp = info->getHeaders();
    this->env["CONTETNT_LENGTH"] = itoa(strlen(info->getBody()));
    this->env["CONTENT_TYPE"] = tmp["Content-Type"];
    this->env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->env["PATH_INFO"] = info->getTarget();
    this->env["PATH_TRANSLATED"] = info->getTarget();
    // this->env["QUERY_STRING"];
    this->env["REMOTE_ADDR"];
    this->env["REMOTE_IDENT"];
    this->env["REMOTE_USER"];
    this->env["REQUEST_METHOD"];
    this->env["SCRIPT_NAME"];
    this->env["SERVER_NAME"];
    this->env["SERVER_PORT"];
    this->env["SERVER_PROTOCOL"];
    this->env["SERVER_SOFTWARE"];

}
