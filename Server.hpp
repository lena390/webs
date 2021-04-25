/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:56:32 by atable            #+#    #+#             */
/*   Updated: 2021/04/24 14:13:02 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Serv.hpp"

class Server
{
    private:
        Serv                _server;
        std::vector<int>    _writefd;
        std::vector<int>    _readfd;
        int                 _maxfd;
        fd_set              _master;
        fd_set              _masterwrt;

        Server();
    public:
        Server( Serv servers );
        ~Server();

        int initServer();
        int startServer();
        void clearServer();
        

};
# endif