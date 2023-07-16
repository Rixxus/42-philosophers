# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmount <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 11:14:37 by rmount            #+#    #+#              #
#    Updated: 2023/07/16 13:18:30 by rmount           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=gcc

CFLAGS=-Wall -Werror -Wextra -pthread -Iheaders/

SRCS=srcs/utils.c \
	srcs/philo.c \
	srcs/init.c \
	srcs/actions.c \
	srcs/clock.c

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
 