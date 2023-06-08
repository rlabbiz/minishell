# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 05:18:06 by rlabbiz           #+#    #+#              #
#    Updated: 2023/06/08 22:16:41 by ael-amin         ###   ########.fr        #
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
		 parser/analyzer.o \
		 parser/parser.o \
		 builtins/builtin1.o \
		 execution/execution.o
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
	@$(CC) $(CFLAGS) -L/Users/ael-amin/.brew/opt/readline/lib -I /Users/ael-amin/.brew/opt/readline/include -lreadline $(OBJECT) $(LIBFT) $(MAIN_FILE) -o $(NAME)
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
