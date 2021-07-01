/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:51:40 by atable            #+#    #+#             */
/*   Updated: 2021/06/09 18:14:48 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONCE_HPP
# define RESPONCE_HPP

# include "headers.hpp"
#include "Request.hpp"

class Request_info;

class Response
{
    private:
        static bool CheckHTTPVersion(Request_info* request_info);
        std::string append_message(std::string & respond, int status_code, std::string & location, Request_info * request);
        std::string HEAD_respond(Request_info * request, std::string & respond, t_serv_config & config);
        static char * get_file_modif_time(const char *path, char * buffer);
        char * get_formatted_date(char * buffer);
        std::string get_content_type(const std::string file_name);
        std::string append_body(Request_info * request, std::string & respond, t_serv_config & config);
        static char * itoa(int d);
        std::string GET_respond(Request_info * request, std::string & respond, t_serv_config & config);
        std::string POST_respond(Request_info * request, std::string & respond, t_serv_config & config);
        std::string DELETE_respond(Request_info * request, std::string & respond, t_serv_config & config);

    public:
        Response();
        ~Response();
        std::string write_response(Request_info *request, t_serv_config & config);
};

#endif