# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atable <atable@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/16 16:05:10 by atable            #+#    #+#              #
#    Updated: 2021/04/16 16:08:55 by atable           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = launch_server.cpp process_request.cpp webserv.cpp
OBJ = $(SRC:.cpp=.o)
HDR = header.hpp

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
