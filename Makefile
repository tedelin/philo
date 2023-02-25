# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 16:02:08 by tedelin           #+#    #+#              #
#    Updated: 2023/02/25 17:08:34 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
INCLUDE = -I.
CFLAGS = -Wall -Wextra -Werror
CC = cc
SRC = 
OBJS = 

all: $(NAME)

$(NAME): OBJS
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re