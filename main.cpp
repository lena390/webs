/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:52:22 by atable            #+#    #+#             */
/*   Updated: 2021/04/26 16:13:29 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "Server.hpp"

Serv fill_server( int port )
{
    Serv serv1(port);
    return serv1;
}

int main()
{
    std::vector<Serv> serv;
    serv.push_back(fill_server(8000));
    serv.push_back(fill_server(8080));
    Server server(serv);
    if (!server.initServer())
    {
        server.startServer();
        server.clearServer();
    }
    return 0;
}