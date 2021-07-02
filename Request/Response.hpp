/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:51:40 by atable            #+#    #+#             */
/*   Updated: 2021/07/02 13:06:08 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONCE_HPP
# define RESPONCE_HPP

# include "../headers.hpp"
# include "../Request/Request.hpp"
# include "../utils/CGI.hpp"

class Request_info;

class Response
{
    private:
        bool CheckHTTPVersion(Request_info* request_info);
        std::string append_message(std::string & respond, int status_code, std::string & location, Request_info * request);
        std::string HEAD_respond(Request_info * request, std::string & respond, t_serv_config & config);
        char * get_file_modif_time(char *path, char * buffer);
        char * get_formatted_date(char * buffer);
        
        std::string get_content_type(const std::string file_name);
        std::string append_body(Request_info * request, std::string & respond, t_serv_config & config);
        std::string GET_respond(Request_info * request, std::string & respond, t_serv_config & config);

    public:
        Response();
        ~Response();
        std::string write_response(Request_info *request, t_serv_config & config);
};

#endif