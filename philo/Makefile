# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 16:02:08 by tedelin           #+#    #+#              #
#    Updated: 2023/03/08 17:37:30 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
INCLUDE = -I.
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
CC = cc
SRC = philo.c utils.c routine.c
OBJS = $(addprefix obj/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) Makefile
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -rf $(OBJS)
	@rm -rf obj

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re