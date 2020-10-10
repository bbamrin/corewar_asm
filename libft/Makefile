# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkathy  <pkathy@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 19:36:16 by pkathy            #+#    #+#              #
#    Updated: 2019/10/26 16:53:46 by pkathy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = $(shell find . | awk -F '/' '/.c$$/ {print $$NF}')

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[104;34mLIBFT  DONE\033[0m"

%.o:%.c libft.h get_next_line.h
	gcc -Wall -Wextra -Werror -O2 -I ./ -c $< -o $@
clean:
	@/bin/rm -rf $(OBJS)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
