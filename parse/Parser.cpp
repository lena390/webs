#include "Parser.hpp"

Parser::Parser(void)
{
    return ;
}

Parser::~Parser(void)
{
    return ;
}

std::vector<std::string> Parser::divide(std::string str, std::string endchar)
{
    std::vector<std::string> ret;
    char *cho;
    int i;

    str += endchar[0];
    std::string::size_type start = str.find_first_not_of(endchar, 0);
    std::string::size_type end = 0;
    while (1)
    {
        end = str.find_first_of(endchar, start);
        if (end == std::string::npos)
            break ;
        std::string res = str.substr(start, end - start);
        ret.push_back(res);
        if ((start = str.find_first_not_of(endchar, end)) == std::string::npos)
            break ;
    }
    return (ret);
}

std::vector<std::string> Parser::readConfig(const char *filename)
{
    std::string line ="";
    int fd;
    int buff_size = 1024;
    int i = 0;
    int j = 0;
    char buff[buff_size];
    std::vector<std::string> file;
    for (j = 0; j < buff_size; j++)
        buff[j] = '\0';
    if ((fd = open(filename, O_RDONLY)) <= 0)
        throw Parser::FileNotFoundException();
    for (i = buff_size; i > 0; i = read(fd, buff, buff_size))
    {
        buff[i] = '\0';
        line += buff;
    }

    if (i == -1)
    {
        std::cerr << "Error in reading config file." << std::endl;
        return file;
    }

    file = Parser::divide(line, std::string(" \n\t\r"));
    return file;
}

const char *Parser::FileNotFoundException::what() const throw()
{
    return ("Exception: Can't find config file");
}

//тест чтения файла
// int main(void)
// {
//     Parser raz;
//     std::vector<std::string> res;

//     res = raz.readConfig("./testconf/serv.conf");
//     for(int i = 0; i < res.size(); i++)
//         std::cout << res[i] << "!"<< std::endl;
//     return (0);
// }