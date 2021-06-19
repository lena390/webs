/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:56:32 by atable            #+#    #+#             */
/*   Updated: 2021/06/08 16:51:09 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Serv.hpp"

class Server
{
    private:
        std::vector<Serv>       _tmp;
        std::map<int, Serv>     _server;
        std::map<int, Serv*>    _client;
        std::vector<int>        _write;
        int                     _maxfd;
        fd_set                  _master;
        fd_set                  _masterwrt;

        Server( void );
    public:
        Server( std::vector<Serv> const & serv );
        ~Server();

        int initServer();
        int startServer();
        void clearServer();
        

};
# endif