#ifndef INSIDE_HPP
# define INSIDE_HPP

# include "Servers.hpp"
# include <map>
# include "ft_atoi.hpp"
# include <limits>

typedef struct s_listen {
    std::string host;
    int port;
}               t_listen;

class Inside
{
    public:
        Inside(void);
        virtual ~Inside(void);
        int     writeInside(int &i, std::vector<std::string> &file);

        class ExceptionBadArgument: public std::exception
        {
            virtual const char *what() const throw();
        };

        std::vector<t_listen>           getListen() const;
        std::string                     getRoot() const;
        std::vector<std::string>        getServerName() const;
        std::map<std::string, Inside>   getLocation() const;
        void                            transferArgs(Inside &server) const;
        static Inside                   initdefaultServ(const char *filename);

        bool                            isNumber(const std::string &str);
        int                             decipherIp(std::string Ip);
    private:
        std::vector<t_listen>           listen;
        std::string                     root;
        std::vector<std::string>        server_name;
        std::map<std::string, Inside>   location;

        static std::map<std::string, void (Inside::*)(std::vector<std::string>)>    serverMap;
        static std::map<std::string, void (Inside::*)(std::vector<std::string>)>    locationMap;
        static std::map<std::string, void (Inside::*)(std::vector<std::string>)>    initServMap();
        static std::map<std::string, void (Inside::*)(std::vector<std::string>)>    initLocateMap();
        static Inside                                                               defaultServer;

        void                            initListen(std::vector<std::string> arg);
        void                            initRoot(std::vector<std::string> arg);
        void                            initServerName(std::vector<std::string> arg);


        int                             readLocation(int &i, std::vector<std::string> &file);


};

#endif