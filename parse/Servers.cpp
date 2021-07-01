#include "Servers.hpp"

Servers::~Servers()
{
    return ;
}

Servers::Servers()
{
    return ;
}

std::vector<Inside>    Servers::getServs() const
{
    return (this->servs);
}

int Servers::parsing(const char *filename)
{
    std::vector<std::string>    file;

    file = Parser::readConfig(filename);
    for (int i = 0; i < file.size(); i++)
    {
        if (file[i] != "server")
        {
            std::cerr << "Error: unknown [" << file[i] << "]" << std::endl;
            return (1);
        }
        else
        {
            Inside serv; //!!!
            i++;
            if (file[i] != "{")
            {
                std::cerr << "Error: no '{' after server directive" << std::endl;
                return (1);
            }
            i++;
            // if (!serv.writeInside(i, file)); //!!!
            // {
            //     //std::cout << file[i] << " !!! " << i << std::endl;
            //     std::cerr << "Error: invalid config file [" << filename << "]" << std::endl;
            //     return (1);
            // }
            serv.writeInside(i, file);
            this->servs.push_back(serv); //!!!!
        }
    }
    return (0);
}