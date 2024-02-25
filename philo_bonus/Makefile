# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 21:23:33 by aachalla          #+#    #+#              #
#    Updated: 2024/02/25 18:28:18 by aachalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main_bonus.c parsing_and_init_bonus.c utils_bonus.c philos_bonus.c
HEADER = philo_bonus.h
OBJ = $(SRC:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra -pthread
NAME = philo_bonus

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
