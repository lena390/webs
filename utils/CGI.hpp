/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:03:49 by atable            #+#    #+#             */
/*   Updated: 2021/07/06 14:16:17 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "../headers.hpp"
# include "../Request/Request.hpp"
# include "../parse/Inside.hpp"

class Request_info;

class CGI
{
    public:
        CGI( Request_info *, Inside & );
        ~CGI( void );
        
        std::string startCGI( const std::string & );

    private:
        CGI( void );
        CGI( CGI const & );
        
        char **to_array( void );
        void clearEnvArr( char ** );

        std::map<std::string, std::string> _env;
        char* _body;
        
};

# endif