/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:52:22 by atable            #+#    #+#             */
/*   Updated: 2021/07/02 13:07:51 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "Server/Server.hpp"
#include "parse/Servers.hpp"
#include "parse/Inside.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << RED << "Too many arguments" << RESET << std::endl;
        return -1;
    }

    Servers config;
    int ret;
    try
    {
        ret = config.parsing(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if (ret == 1)
        return 0;
    
    
    Server server(config.getServs());
    if (server.initServer() == -1 || server.startServer() == -1)
        std::cout << RED << "Server ERROR" << RESET << std::endl;
    

    return 0;
}