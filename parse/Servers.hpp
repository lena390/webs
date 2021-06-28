#ifndef SERVERS_HPP
# define SERVERS_HPP

# include "Parser.hpp"
# include "Inside.hpp"

class Inside;

class Servers
{
    public:
        virtual ~Servers();
        Servers();
        int     parsing(const char *filename);

        std::vector<Inside>    getServs() const;
    private:
        std::vector<Inside> servs;
};

#endif