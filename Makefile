# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 05:18:06 by rlabbiz           #+#    #+#              #
#    Updated: 2023/04/07 17:32:16 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJECT = minishell_ultis.o
MAIN_FILE = minishell.c
DEPS = minishell.h

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(MAIN_FILE) $(OBJECT) $(DEPS)
	@$(CC) $(CFLAGS) -lreadline $(OBJECT) $(MAIN_FILE) -o $(NAME)
	@echo "\t The $(NAME) is created. "

.PHONY: all re clean fclean

clean:
	@rm -rf *.o
	@echo "\t The object files is removed. "

fclean: clean
	@rm -rf $(NAME)
	@echo "\t The $(NAME) is removed. "

re: fclean all
