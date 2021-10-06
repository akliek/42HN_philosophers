# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akliek <akliek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 13:09:04 by akliek            #+#    #+#              #
#    Updated: 2021/10/05 11:09:17 by akliek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = philo.c	\
	validation.c	\
	init.c	\
	utils.c	\
	routine.c	\
	print.c	\
	finish.c

OBJ :=  $(SRC:.c=.o)

all: $(NAME)

$(NAME):
		$(CC) -c $(CFLAGS) $(SRC)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re:	
		make fclean
		make all
