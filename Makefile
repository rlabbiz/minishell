# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 05:18:06 by rlabbiz           #+#    #+#              #
#    Updated: 2023/05/22 21:44:05 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJECT = minishell_ultis.o \
		 check_args.o \
		 prompt.o \
		 memory.o \
		 parser/convert_to_cmd.o \
		 parser/analyzer.o 
MAIN_FILE = minishell.c
DEPS = minishell.h
LIBFT = libft/libft.a

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(LIBFT):
	@make bonus -C libft
	@make -C libft

$(NAME): $(MAIN_FILE) $(OBJECT) $(DEPS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECT) $(MAIN_FILE) $(LIBFT) -o $(NAME) -lreadline 
	@echo "\t The $(NAME) is created. "

.PHONY: all re clean fclean

clean:
	@rm -rf $(OBJECT)
	@make clean -C libft
	@echo "\t The object files is removed. "

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo "\t The $(NAME) is removed. "

re: fclean all
