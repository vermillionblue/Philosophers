# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 11:40:59 by danisanc          #+#    #+#              #
#    Updated: 2022/11/19 18:31:44 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c actions.c utils.c ft_atol.c time.c init.c check_destroy.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -pthread $(OBJ) -o $(NAME) 

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

#-g -fsanitize=address -g  -fsanitize=thread