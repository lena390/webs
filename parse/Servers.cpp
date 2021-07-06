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
            //std::cout << i << std::endl;
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

// int main(void)
// {
//     Servers raz;

//     raz.parsing("./testconf/serv.conf");

//     //print root
//     std::cout << (raz.getServs())[0].getRoot() << std::endl;

//     //print server_name
//     std::cout << (raz.getServs())[1].getServerName()[0] << std::endl;


    //print listen
    std::cout << " LISTEN " << std::endl << std::endl;
    std::cout << (raz.getServs())[0].getListen().port << std::endl;
    std::cout << (raz.getServs())[1].getListen().port << std::endl;
    std::cout<< std::endl;


//     //print error_page
//     std::cout << (raz.getServs())[1].getErrorPage().begin()->first << std::endl;
//     std::cout << (raz.getServs())[1].getErrorPage().begin()->second << std::endl;

//     //print methods
//     std::cout << *(raz.getServs())[0].getMethods().begin() << std::endl;

    //print cgi param
    // std::cout << (raz.getServs())[1].getLocation().begin()->second.getCgiParam().begin()->first << std::endl;
    // std::cout << (raz.getServs())[1].getLocation().begin()->second.getCgiParam().begin()->second << std::endl;

    //print Client Body Size
    std::cout << (raz.getServs())[0].getClientBodySize() << std::endl;

    //print autoindex
    std::cout << "autoindex = " << (raz.getServs())[0].getAutoIndex() << std::endl;

    //print autoindex
    std::cout << "autoindex = " << (raz.getServs())[0].getAutoIndex() << std::endl;

    //print location
    std::map<std::string, Inside>::iterator it;
    it = raz.getServs()[0].getLocation().begin();
    
    std::cout <<it->first<<std::endl;
    std::cout <<it->second.getRoot()<<std::endl;
    it++;
    std::cout <<it->first<<std::endl;

    std::cout << "NEW LOCATION" << std::endl << std::endl;

    // Inside config;
    // std::string locName = "/abc" ;
    // std::string root = "/";
    // std::string errorpage = "/error";
    // std::map<int, std::string> error;
    // std::string cgi = "/huh";
    // std::set<std::string> meth;
    // meth.insert("/kok");
    // std::vector<std::string> index;
    // index.push_back("cooll");
    // error[399] = errorpage;
    // // root   errorpage       method   clientBodySize  cgiPass  Index    autoindex
    // // str  map(int, str)     set(str)       int         str    vec(str)   bool
    // config.getLocation()[locName] = new Inside(root, error, meth, 2, cgi, index, false);
    return (0);
}