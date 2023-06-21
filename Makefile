# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 05:18:06 by rlabbiz           #+#    #+#              #
#    Updated: 2023/06/21 16:01:51 by ael-amin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror# -fsanitize=address -g
OBJECT = minishell_ultis.o \
		 check_args.o \
		 prompt.o \
		 memory.o \
		 parser/lexar.o \
		 parser/lexar_quotes.o \
		 parser/analyzer.o \
		 parser/parser.o \
		 builtins/get_the_env.o \
		 builtins/builtins1.o \
		 builtins/builtins2.o \
		 builtins/main_builtins.o \
		 builtins/utils_env.o \
		 execution/exec.o \
		 execution/second_exec.o \
		 execution/case_builtins.o \
		 parser/parser_ultis.o \
		 parser/redirection.o \
		 parser/herdoc.o \
		 parser/analyzer_ultis.o \
		 parser/lexar_quotes_ultis.o \
		 parser/expand.o
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

# @$(CC) $(CFLAGS) -L/Users/rlabbiz/.brew/opt/readline/lib -I /Users/rlabbiz/.brew/opt/readline/include -lreadline $(OBJECT) $(LIBFT) $(MAIN_FILE) -o $(NAME)

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
