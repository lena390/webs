# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atable <atable@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 20:50:00 by atable            #+#    #+#              #
#    Updated: 2021/07/07 17:52:46 by atable           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = Server/Server.cpp Server/Serv.cpp Request/Response.cpp Request/Request.cpp main.cpp utils/utils.cpp utils/CGI.cpp utils/Autoindex.cpp
PARSE_SRC = parse/ft_atoi.cpp parse/Inside.cpp parse/Parser.cpp parse/Servers.cpp 

OBJ = $(SRC:.cpp=.o)
PARSE_OBJ = $(PARSE_SRC:.cpp=.o)

HDR = Request/Request.hpp headers.hpp Server/Server.hpp Server/Serv.hpp Request/Response.hpp utils/CGI.hpp
PARSE_HDR = parse/ft_atoi.hpp parse/Inside.hpp parse/Parser.hpp parse/Servers.hpp

CC = clang++
FLAGS = -Wall -Werror -Wextra
SYS = -std=c++98
DBG = -g

.Phony: re clean fclean all

all: $(NAME)

$(NAME): $(HDR) $(PARSE_HDR) $(SRC) $(PARSE_SRC)
	$(CC) $(SRC) $(PARSE_SRC) -o $(NAME) 

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
