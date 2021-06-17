/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:12:39 by atable            #+#    #+#             */
/*   Updated: 2021/06/09 20:20:42 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_HPP
# define HEADERS_HPP

# include <iostream>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <netdb.h>
# include <time.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fstream>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "fcntl.h"
# include <sys/ioctl.h>

# include <sstream>

# include <vector>
# include <map>
# include <string>

# include <ctime>
# include <fstream>
# include <sys/stat.h>

# define RED    "\033[31m"
# define GREEN  "\033[32m"
# define RESET  "\033[0m"

# define BUF_SIZE   65536

// Костыль, который нужно удалить, после того, как Глеб напишет свою часть
typedef struct s_conf {
    std::string locations = "/start_page.html";
    std::string method = "GET";
} t_serv_config;

int print_error(std::string err, int status);

#endif