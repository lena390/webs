# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atable <atable@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 20:50:00 by atable            #+#    #+#              #
#    Updated: 2021/06/09 18:22:14 by atable           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = Server.cpp Serv.cpp Response.cpp Request.cpp main.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)
HDR = Request.hpp headers.hpp Server.hpp Serv.hpp Response.hpp

CC = clang++
FLAGS = -Wall -Werror -Wextra
SYS = -std=c++98
DBG = -g

.Phony: re clean fclean all

all: $(NAME)

$(NAME): $(HDR) $(SRC)
	$(CC) $(SRC) -o $(NAME) 

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
