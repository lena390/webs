/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:03:49 by atable            #+#    #+#             */
/*   Updated: 2021/06/28 12:47:44 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "headers.hpp"
# include "Request.hpp"

class Request_info;

class CGI
{
    public:
        CGI( Request_info *, t_serv_config );
        ~CGI( void );


    private:
        CGI( void );
        CGI( CGI const & );

        std::map<std::string, std::string> env;
        
};

# endif