/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:50 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/17 20:28:57 by rlabbiz          ###   ########.fr       */
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
# define NONE 0

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
	int		herdoc;
	int		first_rdr;
	int 	cmd_len;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char *name;
	char *value;
}	t_env;

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
t_cmd	*parser(t_list *list, t_list *lst_env);
int		check_quotes(char *input);
int		check_if_quotes(char *str, int i, int *quotes);
int		find_quotes(char *str, int i, int *quotes);
void	quotes_error(int type);
int		get_cmd_line(t_list *list);
void	get_arrgs_supp(t_list *node, t_cmd *cmd, int len, int cmd_len);
t_cmd	get_args(t_list *lst, int cmd_len);
char	*get_herdoc(void);
int		check_onbiges(char *file);
void	redirections_in(t_cmd **lst, char *file);
int		redirections_out(t_cmd **lst, char *file);
int		redirections_append(t_cmd **lst, char *file);
void	redirections_herdoc(t_cmd **lst);
int		redirections(t_cmd *cmd, char *str, int rdr, t_list *lst_env);
void	herdoc_supp(t_list *lst_env, char *herdoc, int fd, int expand);
int		herdoc(char *file, t_list *lst_env, int expand);
int		read_herdocs(t_list *lst, t_list *lst_env);
void	write_expantion(t_list *lst_env, char *herdoc, int fd);
int		parser_supp1(t_cmd **lst, t_list *node, t_list *lst_env, int i);
int		parser_supp(t_cmd **lst, t_list *node, t_list *lst_env, int len);
// build-in ---- env
t_env	*get_value_of_env(t_list **lst, char *str);
t_list	*get_env(t_list **lst, char **str);
char	*get_env_value(t_list *lst, char *name);
void	export_env(t_list **lst, char *old_str);
void	del_env(void *ptr);
void	unset_env(t_list **lst, char *name);
void	print_env(t_list *lst);

// excuetion
void	execution(t_cmd *cmd, t_list **lst_env);
char	*expantion(char *str, t_list *lst_env, int check);
t_list	*write_expantion_on_lst(t_list *lst_env, char *str);


#endif
