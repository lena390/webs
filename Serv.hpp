/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serv.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:02:10 by atable            #+#    #+#             */
/*   Updated: 2021/04/26 12:57:02 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERV_HPP
# define SERV_HPP

#include "headers.hpp"

class Serv
{
	private:
		std::map<int, std::string>	_request;
		int                 		_port;
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
		
};

#endif