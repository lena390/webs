/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serv.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:02:10 by atable            #+#    #+#             */
/*   Updated: 2021/04/24 12:32:42 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERV_HPP
# define SERV_HPP

#include "headers.hpp"

class Serv
{
    private:
        int _socket;
        int _port;
        struct sockaddr_in _addr;
        
        
    
    public:
        Serv( void );
        Serv( int );
        Serv( const Serv & serv );
        ~Serv( void );

        void initServer( void );
        int connectServer( void );
        int getSocket( void );
        void closeSock( void );
        struct sockaddr_in & getAddress( void );
};

#endif