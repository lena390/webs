/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:28:42 by atable            #+#    #+#             */
/*   Updated: 2021/07/07 12:03:22 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers.hpp"

int print_error(std::string err, int status)
{
    std::cerr << err << std::endl;
    return(status);
}

char * itoa(int d) {
    int length = 0;
    int copy = d;
    while (copy) {
        length++;
        copy = copy / 10;
    }
    if (length == 0)
        return strdup("0");
    char str[length + 1];
    str[length] = '\0';
    int i = length - 1;
    while (d) {
        int j = d % 10;
        d = d / 10;
        str[i--] = j + 48;
    }
    return strdup(str);
}

char * toCharStr( std::string str )
{
    int len = str.length();
    char *buf = new char[len];
    for (int i = 0; i < len; i++)
        buf[i] = str[i];
    buf[len] = '\0';
    return buf;
}

char * strcut( char * start, char * end, int size )
{
    if (!start || !end)
        return NULL;
    if (*start == '\0')
        return NULL;
    char * newStr = new char[size];
    int i = 0;
    while (start != end)
    {
        newStr[i] = *start;
        start++;
        i++;
    }
    newStr[i] = '\0';
    return newStr;        
}