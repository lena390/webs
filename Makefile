# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atable <atable@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 20:50:00 by atable            #+#    #+#              #
#    Updated: 2021/04/20 20:51:47 by atable           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = Server.cpp Serv.cpp main.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)
HDR = headers.hpp Server.hpp Serv.hpp

CC = clang++
FLAGS = -Wall -Werror -Wextra
SYS = -std=c++98
DBG = -g

.Phony: re clean fclean all

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
