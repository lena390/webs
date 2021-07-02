/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:56:32 by atable            #+#    #+#             */
/*   Updated: 2021/07/02 13:04:50 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Serv.hpp"
#include "../parse/Inside.hpp"

class Server
{
	private:
		std::vector<Inside>     _info;
		std::map<int, Serv>     _server;
		std::map<int, Serv*>    _client;
		std::vector<int>        _write;
		int                     _maxfd;
		fd_set                  _master;
		fd_set                  _masterwrt;

		Server( void );
	public:
		Server( std::vector<Inside> const & serv );
		~Server();

		int initServer();
		int startServer();
		void clearServer();
		

};
# endif