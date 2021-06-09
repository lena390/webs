/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:31:08 by atable            #+#    #+#             */
/*   Updated: 2021/06/09 17:44:05 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request_info::Request_info( void ) { return ; } 

Request_info::Request_info(char *buffer) : correct_(true), request_(buffer) {
    char *start = buffer;
    //parsing method
    char *str_occurrence = strchr(start, '/');
    if (str_occurrence == NULL) {
        correct_ = false;
        false_reason_ = "no method found\n";
        return;
    }
    method_ = strndup(start, str_occurrence - start - 1);//
    start = str_occurrence + 1;
    if (start == NULL) {
        correct_ = false;
        false_reason_ = "request is incomplete\n";
        return;
    }
    //parsing request target
    str_occurrence = strstr(start, " HTTP/");
    if (str_occurrence == NULL) {
        correct_ = false;
        false_reason_ = "no HTTP version found\n";
        return;
    }
    if (start != str_occurrence) {
        request_target_ = strndup(start, str_occurrence - start);
    }
    //parsing http version
    std::string s(str_occurrence + 6, 3);
    HTTP_version_ = s;
    start = strstr(start, "\r\n") + 1;
    if (start == NULL) {
        correct_ = false;
        false_reason_ = "request is incomplete\n";
        return;
    }
    //parsing headers
    while (strstr(start, ": ")) {
        char* key;
        char* value;

        str_occurrence = strstr(start, ": ");
        key = strndup(start, str_occurrence - start);

        start = str_occurrence + 2;
        str_occurrence = strstr(start, "\r\n");
        value = strndup(start, str_occurrence - start);
        start = str_occurrence + 2;
        headers_[key] = value;
       // free(key);
       // free(value);
    }
    start += 2;
    str_occurrence = strchr(start, '\0');
    body_ = strndup(start, str_occurrence - start);
}

Request_info::Request_info(Request_info & other) {
    correct_ = other.isCorrect();
    false_reason_ = other.getFalseReason();
    method_ = other.getMethod();
    request_target_ = other.getTarget();
    HTTP_version_ = other.getVersion();
    headers_ = other.getHeaders();
    body_ = other.getBody();
    request_ = other.getRequest();
}