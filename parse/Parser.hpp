#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <string>
# include <exception>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <iostream>
# include <unistd.h>

class Parser
{
    public:
        Parser(void);
        virtual ~Parser(void);
        static std::vector<std::string> readConfig(const char *filename);
        static std::vector<std::string> divide(std::string str, std::string endchar);
        class FileNotFoundException: public std::exception
        {
            virtual const char  *what() const throw();
        };
};

#endif