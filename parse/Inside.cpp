#include "Inside.hpp"

t_listen              Inside::getListen() const
{
    return (this->listen);
}

std::string                         Inside::getRoot() const
{
    return (this->root);
}

std::vector<std::string>            Inside::getServerName() const
{
    return (this->server_name);
}

std::map<std::string, Inside>       Inside::getLocation() const
{
    return (this->location);
}

std::map<int, std::string>          Inside::getErrorPage() const
{
    return (this->error_page);
}

std::set<std::string>               Inside::getMethods() const
{
    return (this->methods);
}

int                                 Inside::getClientBodySize() const
{
    return (this->client_body_size);
}

std::string                         Inside::getCgiPass() const
{
    return (this->cgi_pass);
}

std::map<std::string, std::string>  Inside::getCgiParam() const
{
    return (this->cgi_param);
}

std::vector<std::string>            Inside::getIndex() const
{
    return (this->index);
}

std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::initServMap()
{
    std::map<std::string, void (Inside::*)(std::vector<std::string>)> init;
    init["listen"] = &Inside::initListen;
    init["root"] = &Inside::initRoot;
    init["server_name"] = &Inside::initServerName;
    init["error_page"] = &Inside::initErrorPage;
    init["methods"] = &Inside::initMethods;
    init["client_body_size"] = &Inside::initClientBodySize;
    init["cgi_pass"] = &Inside::initCgiPass;
    init["cgi_param"] = &Inside::initCgiParam;
    init["index"] = &Inside::initIndex;
    return (init);
}

std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::initLocateMap()
{
    std::map<std::string, void (Inside::*)(std::vector<std::string>)> init;
    init["root"] = &Inside::initRoot;
    init["error_page"] = &Inside::initErrorPage;
    init["methods"] = &Inside::initMethods;
    init["client_body_size"] = &Inside::initClientBodySize;
    init["cgi_pass"] = &Inside::initCgiPass;
    init["cgi_param"] = &Inside::initCgiParam;
    init["index"] = &Inside::initIndex;
    return (init);
}

std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::serverMap = Inside::initServMap();
std::map<std::string, void (Inside::*)(std::vector<std::string>)> Inside::locationMap = Inside::initLocateMap();
Inside      Inside::defaultServer = Inside();

Inside::Inside(void):
root(""),
client_body_size(0)
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
            // for (std::vector<t_listen>::const_iterator i = listen.begin(); i != listen.end(); i++)
            // {
            //     if (i->port == list.port)
            //         throw Inside::ExceptionBadArgument();
            // }
            this->listen = list;

            return ;
        }
        throw Inside::ExceptionBadArgument();
    }
    else
    {
        list.host = arg[0].substr(0, sep);
        if (list.host == "localhost")
            list.host = "127.0.0.1";
        sep++;
        pstr = arg[0].substr(sep);
        if (isNumber(pstr))
        {
            list.port = ft_atoi(pstr.c_str());
            this->listen = list;
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
        throw Inside::ExceptionBadArgument();
    for (int i = 0; i < arg.size(); i++)
        this->server_name.push_back(arg[i]);
}

void    Inside::initErrorPage(std::vector<std::string> arg)
{
    size_t              length = arg.size();
    std::string         hz;
    std::vector<int>    ret_code;

    for (size_t i = 0; i < length; i++)
    {
        if (isNumber(arg[i]))
            ret_code.push_back(ft_atoi(arg[i].c_str()));
        else if (ret_code.empty())
            throw Inside::ExceptionBadArgument();           
        else if (i == length - 1)
            hz = arg[i];
        else
            throw Inside::ExceptionBadArgument();
    }
    if (hz == "")
        throw Inside::ExceptionBadArgument();
    for (std::vector<int>::iterator j = ret_code.begin(); j != ret_code.end(); j++)
        this->error_page[*j] = hz;
}

void    Inside::initMethods(std::vector<std::string> arg)
{
    if (arg.empty())
        throw Inside::ExceptionBadArgument();
    this->methods.clear();
    for(std::vector<std::string>::iterator it = arg.begin(); it != arg.end(); it++)
    {
        this->methods.insert(*it);
    }
}

void    Inside::initClientBodySize(std::vector<std::string> arg)
{
    if (arg.size() != 1 || !isNumber(arg[0]))
    {
        std::cout << isNumber(arg[0]) << std::endl;
        throw Inside::ExceptionBadArgument();
    }
    this->client_body_size = ft_atoi(arg[0].c_str());
}

void    Inside::initCgiPass(std::vector<std::string> arg)
{
    if (arg.size() != 1)
        throw Inside::ExceptionBadArgument();
    this->cgi_pass = arg[0];
}

void    Inside::initCgiParam(std::vector<std::string> arg)
{
    if (arg.size() != 2)
        throw Inside::ExceptionBadArgument();
    this->cgi_param[arg[0]] = arg[1];
}

void    Inside::initIndex(std::vector<std::string> arg)
{
    if (arg.empty())
        throw Inside::ExceptionBadArgument();
    this->index.insert(this->index.end(), arg.begin(), arg.end());
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
                    return (0);
                locationName = file[i];
                i++;
                if (!locate.readLocation(i, file))
                    return (0);
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
        for (std::map<std::string, Inside>::iterator i = this->location.begin(); i != this->location.end(); i++)
            this->transferArgs(i->second);
        return (1);
    }
    return (0);
}

int     Inside::readLocation(int &i, std::vector<std::string> &file)
{
    std::string     dir="";
    std::vector<std::string>    args;
    std::map<std::string, void (Inside::*)(std::vector<std::string>)>::iterator     it;
    if (file[i++] != "{")
        return (0);
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
                    return (0);
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
        if (serv.getListen().host == "")
            serv.listen = this->listen;
        // if (serv.listen.empty())
        //     serv.listen.insert(serv.listen.begin(), this->listen.begin(), this->listen.end());
        if (serv.root == "")
            serv.root = this->root;
        serv.server_name.insert(serv.server_name.begin(), this->server_name.begin(), this->server_name.end());
    }
    for (std::map<int, std::string>::const_iterator it  = this->error_page.begin(); it != this->error_page.end(); it++)
    {
        if (serv.error_page.find(it->first) == serv.error_page.end())
            serv.error_page[it->first] = it->second;
    }
    if (serv.methods.empty())
        serv.methods = this->methods;
    if (serv.client_body_size == 0)
        serv.client_body_size = this->client_body_size;
    if (serv.cgi_pass == "")
        serv.cgi_pass = this->cgi_pass;
    for(std::map<std::string, std::string>::const_iterator it = this->cgi_param.begin(); it != this->cgi_param.end(); it++)
    {
        if (serv.cgi_param.find(it->first) == serv.cgi_param.end())
            serv.cgi_param[it->first] = it->second;
    }
    serv.index.insert(serv.index.begin(), this->index.begin(), this->index.end());
    for (std::map<std::string, Inside>::iterator it = serv.location.begin(); it != serv.location.end(); it++)
        serv.transferArgs(it->second);
}

const char      *Inside::ExceptionBadArgument::what() const throw()
{
    return ("Exception: bad arguments in config file");
}