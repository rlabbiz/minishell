/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:50 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/31 22:31:28 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// defines to help `conv_to_cd` function.
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

// defines to help the parser
# define RDR_IN 1
# define RDR_OUT 2
# define RDR_APPEND 3
# define RDR_HERDOC 4
# define NONE -1

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
	char	**args;
	int		ifd;
	int		ofd;
	int		inred;
	int		outred;
	int 	cmd_len;
	struct s_cmd	*next;
}	t_cmd;

// split and get token from command
void	split_cmd(char *input, t_list **list);
void	print_stack(t_list *node);
void	ft_del(void *data);
int		check_quotes(char *input);

// analyze the command
int		check_node(t_list *list);
int		check_rdr(char *data);
int		check_pipe(char *data, int first);
char	*check_cmd(char *old_cmd);

// parser
t_cmd *parser(t_list *list);

#endif
