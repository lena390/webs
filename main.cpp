/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:52:22 by atable            #+#    #+#             */
/*   Updated: 2021/04/25 15:32:18 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "Server.hpp"

Serv fill_server( void )
{
    Serv serv1(8000);
    return serv1;
}

int main()
{
    Server serv(fill_server());
    serv.initServer();
    serv.startServer();
    serv.clearServer();
    return 0;
}