#include "Inside.hpp"

std::vector<t_listen>           Inside::getListen() const
{
    return (this->listen);
}

std::string                     Inside::getRoot() const
{
    return (this->root);
}

std::vector<std::string>        Inside::getServerName() const
{
    return (this->server_name);
}

std::map<std::string, Inside>   Inside::getLocation() const
{
    return (this->location);
}

std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::initServMap()
{
    std::map<std::string, void (Inside::*)(std::vector<std::string>)> init;
    init["listen"] = &Inside::initListen;
    init["root"] = &Inside::initRoot;
    init["server_name"] = &Inside::initServerName;
    return (init);
}

std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::initLocateMap()
{
    std::map<std::string, void (Inside::*)(std::vector<std::string>)> init;
    init["listen"] = &Inside::initListen;
    init["root"] = &Inside::initRoot;
    init["server_name"] = &Inside::initServerName;
    return (init);
}

std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::serverMap = Inside::initServMap();
std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::locationMap = Inside::initLocateMap();
Inside      Inside::defaultServer = Inside();

Inside::Inside(void):
root("")
{
    return ;
}

Inside::~Inside(void)
{
    return ;
}

bool Inside::isNumber(const std::string &str)
{
    int res = 0;
    if (str.find_first_not_of("0123456789") == std::string::npos)
        res = 1;
    return (res);
}

// Inside::decipherIp(std::string Ip)
// {
//     size_t  s = 0;
//     size_t  st = 0;
//     int     a;
//     //char    b[4];
//     if (Ip == "localhost")
//         Ip = "127.0.0.1";
//     for (int i = 0; i < 4; i++) //?????
//     {
//         s = Ip.find_first_of('.', s);
//         a = ft_atoi((Ip.substr(st, s)).c_str());
//     }
// }

void    Inside::initListen(std::vector<std::string> arg)
{
    t_listen    list;
    size_t      sep;
    std::string pstr;
    if (arg.size() != 1)
        throw Inside::ExceptionBadArgument();
    if ((sep = arg[0].find(":")) == std::string::npos)
    {
        if (isNumber(arg[0]))
        {
            list.port = ft_atoi(arg[0].c_str());
            list.host = "";
            for (std::vector<t_listen>::const_iterator i = listen.begin(); i != listen.end(); i++)
            {
                if (i->port == list.port)
                    throw Inside::ExceptionBadArgument();
            }
            this->listen.push_back(list);
            return ;
        }
        throw Inside::ExceptionBadArgument();
    }
    else
    {
        list.host = arg[0].substr(0, sep); //decipherIp(arg[0].substr(0, sep));
        if (list.host == "localhost")
            list.host = "127.0.0.1";
        sep++;
        pstr = arg[0].substr(sep);
        if (isNumber(pstr))
        {
            list.port = ft_atoi(pstr.c_str());
            this->listen.push_back(list);
            return ;
        }
        throw Inside::ExceptionBadArgument();
    }
}

void    Inside::initRoot(std::vector<std::string> arg)
{
    if (arg.size() != 1 || this->root != "")
        throw Inside::ExceptionBadArgument();
    this->root = arg[0];
}

void    Inside::initServerName(std::vector<std::string> arg)
{
    if (arg.size() == 0)
    {
        throw Inside::ExceptionBadArgument();
    }
    for (int i = 0; i < arg.size(); i++)
        this->server_name.push_back(arg[i]);
}

int Inside::writeInside(int &i, std::vector<std::string> &file)
{
    std::map<std::string, void (Inside::*)(std::vector<std::string>)>::iterator     it;
    std::string     dir;
    std::vector<std::string>    args;
    for ( ; i < file.size() && file[i] != "}" ; i++)
    {
        if ((it = Inside::serverMap.find(file[i])) == Inside::serverMap.end())
        {
            if (file[i] == "location")
            {
                //std::cout << file[i] << " !!! " << i << std::endl;
                Inside  locate;
                std::string locationName;
                if (dir != "")
                {
                    (this->*Inside::serverMap[dir])(args);
                    args.clear();
                    dir = "";
                }
                i++;
                if (file[i] == "{" || file[i] == "}")
                {
                    //std::cout << "!!!!!!!!!!" << std::endl;
                    return (0);
                }
                locationName = file[i];
                i++;
                //std::cout << locationName << std::endl;
                if (!locate.readLocation(i, file))
                {
                    //std::cout << "!!!!!!!!!!" << std::endl;
                    return (0);
                }
                this->location[locationName] = locate;
                if (file[i] == "}")
                    continue;
            }
            else if (dir == "")
            {
                //std::cout << "!!!!!!!!!!" << std::endl;
                return file[i] == "}" ? 1 : 0;
            }
            else
                args.push_back(file[i]);
        }
        else
        {
            if (dir != "")
            {
                (this->*Inside::serverMap[dir])(args);
                args.clear();
            }
            dir = it->first;
        }
    }
    if (dir != "")
        (this->*Inside::serverMap[dir])(args);
    if (file[i] == "}")
    {
        Inside::defaultServer.transferArgs(*this);
        for (std::map<std::string, Inside>::iterator i = this->location.begin(); i != this->location.end(); i++)
            this->transferArgs(i->second);
        //std::cout << file[i] << " !!! " << i << std::endl;
        //std::cout << "!!!!!!!!!!" << std::endl;
        return (1);
    }
    //std::cout << "!!!!!!!!!!" << std::endl;
    return (0);
}

int     Inside::readLocation(int &i, std::vector<std::string> &file)
{
    std::string     dir="";
    std::vector<std::string>    args;
    std::map<std::string, void (Inside::*)(std::vector<std::string>)>::iterator     it;
    if (file[i++] != "{")
    {
        //std::cout << "!!!!!!!!!!" << std::endl;
        return (0);
    }
    for (; i < file.size() && file[i] != "}"; i++)
    {
        if ((it = Inside::serverMap.find(file[i])) == Inside::serverMap.end())
        {
            if (file[i] == "location")
            {
                Inside  locate;
                std::string locationName;
                if (dir != "")
                {
                    (this->*Inside::locationMap[dir])(args);
                    args.clear();
                    dir = "";
                }
                i++;
                if (file[i] == "{" || file[i] == "}")
                    return (0);
                locationName = file[i];
                i++;
                if (!locate.readLocation(i, file))
                {
                    //std::cout << "!!!!!!!!!!" << std::endl;
                    return (0);
                }
                this->location[locationName] = locate;
                if (file[i] == "}")
                    continue;
            }
            else if (dir == "")
                return file[i] == "}" ? 1 : 0;
            else
                args.push_back(file[i]);
        }
        else
        {
            if (dir != "")
            {
                (this->*Inside::locationMap[dir])(args);
                args.clear();
            }
            dir = it->first;
        }
    }
    if (dir != "")
        (this->*Inside::locationMap[dir])(args);
    if (file[i] == "}")
        return (1);
    return (0);
}

void    Inside::transferArgs(Inside &serv) const
{
    if (this != &serv)
    {
        if (serv.listen.empty())
            serv.listen.insert(serv.listen.begin(), this->listen.begin(), this->listen.end());
        if (serv.root == "")
            serv.root = this->root;
        serv.server_name.insert(serv.server_name.begin(), this->server_name.begin(), this->server_name.end());
    }
    for (std::map<std::string, Inside>::iterator it = serv.location.begin(); it != serv.location.end(); it++)
        serv.transferArgs(it->second);
}

const char      *Inside::ExceptionBadArgument::what() const throw()
{
    return ("Exception: bad arguments in config file");
}