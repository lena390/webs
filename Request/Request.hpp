/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:30:30 by atable            #+#    #+#             */
/*   Updated: 2021/07/02 13:06:23 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "../headers.hpp"
#include "../Request/Response.hpp"

class Request_info {
    private:
        bool correct_;
        const std::string false_reason_;
        const std::string method_;
        const std::string request_target_;
        const std::string HTTP_version_;
        const std::string qwery_string;
        std::map<std::string, std::string> headers_;
        const char* body_;
        const char* request_;
    
    public:
        Request_info();
        Request_info(char *buffer);
        Request_info(Request_info &);
        ~Request_info() { headers_.clear(); }
        Request_info & operator=(const Request_info &) { return *this; }

        bool isCorrect() const { return correct_;}
        std::string getFalseReason() const { return false_reason_; }
        std::string getMethod() const { return method_; }
        std::string getTarget() const { return request_target_; }
        std::string getVersion() const { return HTTP_version_; }
        std::map<std::string, std::string> getHeaders() { return headers_; }
        char* getBody() const { return body_; }
        char* getRequest() const { return request_; }
};

#endif