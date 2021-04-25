/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:12:39 by atable            #+#    #+#             */
/*   Updated: 2021/04/20 21:48:04 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_HPP
# define HEADERS_HPP

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "fcntl.h"
#include <sys/ioctl.h>

#include <vector>
#include <map>

int print_error(std::string err, int status);

#endif