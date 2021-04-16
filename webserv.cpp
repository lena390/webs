#include "header.hpp"

int main()
{
    bigass_struct config_info;
    struct sockaddr_in addr;
    int sockfd;

    parse_config_file(config_info);
    if (config_info.is_correct)
    {
        sockfd = launch_server(config_info, addr);
        while (1)
        {
            process_request(config_info, addr, sockfd);
        }
    }
    else
    {
        std::cout << "Error: config parsing error\n";
    }
}

void parse_config_file(bigass_struct &bas)
{
    std::string line;
    std::ifstream config_file("config.uiuiui", std::ios::in);

    if (config_file.is_open())
    {
        //init_info_struct(bas);
        while (getline(config_file, line))
        {
            //cout << line << '\n';
            //parse_line(line);
        }
        config_file.close();
        bas.is_correct = 1;
    }
    else
    {
        std::cout << "Unable to open file\n";
        bas.is_correct = 0;
    }
}