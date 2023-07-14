# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmount <rmount@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 11:14:37 by rmount            #+#    #+#              #
#    Updated: 2023/07/14 11:21:44 by rmount           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=gcc

CFLAGS=-Wall -Werror -Wextra -pthread -Iheader/

SRCS=srcs/*.c

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
 