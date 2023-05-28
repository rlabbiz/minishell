/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:50 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/23 19:47:52 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

// defines to help `conv_to_cd` function.
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

// struct used to helpe `conv_to_cd` function.
typedef struct s_conv
{
	int	start;
	int	end;
	int	check;
	int	quotes;
}	t_conv;

typedef struct s_cmd
{
	char	*arg;
	int		fd;
	int		type;
}	t_cmd;

// split and get token from command
void	split_cmd(char *input, t_list **list);
void	print_stack(t_list *node);
void	ft_del(void *data);
int		check_quotes(char *input);

// analyze the command
int		check_node(t_list *list);

#endif
