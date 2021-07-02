/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serv.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:02:10 by atable            #+#    #+#             */
/*   Updated: 2021/07/02 13:05:35 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERV_HPP
# define SERV_HPP

#include "../headers.hpp"
#include "../Request/Response.hpp"
#include "../Request/Request.hpp"

class Serv
{
	private:
		std::map<int, std::string>	_request;
		int							_port;
		struct sockaddr_in  		_addr;

	
	public:
		Serv( void );
		Serv( int );
		Serv( const Serv & serv );
		~Serv( void );

		struct sockaddr_in &			getAddress( void );
		std::map<int, std::string> &	getRequest( void );

		int		connectServer( void );
		void	initServer( void );
		void	closeSock( int );

		int acceptServer( int );
		int recvServer( int );
		int sendServer( int );

		int init_request( int );
		std::stringstream pages_to_stream( std::string );
		
};

#endif