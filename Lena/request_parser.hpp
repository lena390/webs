#pragma once

#include <iostream>
#include <string>
#include <map>

class Request_info {
    private:
        bool correct_;//
        std::string false_reason_;//
        std::string method_;
        std::string request_target_;
        std::string HTTP_version_;
        std::map<std::string, std::string> headers_;
        char* body_;
        char* request_;

        Request_info();
    
    public:
        explicit Request_info(char *buffer);
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

