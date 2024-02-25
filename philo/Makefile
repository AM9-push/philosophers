# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 21:23:33 by aachalla          #+#    #+#              #
#    Updated: 2024/02/25 16:32:16 by aachalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c philos_.c utils.c let_is_.c
HEADER = philo.h
OBJ = $(SRC:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra -pthread
NAME = philo

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
