/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/17 20:23:13 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_expantion(t_list *lst_env, char *herdoc, int fd)
{
	char	*line;
	line = expantion(herdoc, lst_env, 0);
	if (line)
	{
		ft_putstr_fd(line, fd);
		free(line);
	}
}

int parser_supp1(t_cmd **lst, t_list *node, t_list *lst_env, int i)
{
	int		rdr;
	int		check;
	t_cmd	*cmd;

	cmd = *lst;
	if (check_pipe(node->content, 0))
		return (1);
	rdr = check_rdr(node->content);
	if (node->next == NULL)
		return (1);
	if (rdr != 0 && node->next)
	{
		check = redirections(&cmd[i], node->next->content, rdr, lst_env);
			printf("%s\n", cmd[i].args[0]);
		
		printf("here\n");
		if (check == 1 || check == -1)
			return (-1);
		node = node->next;
	}
	if (node->next == NULL)
		return (1);
	return (0);
}

int parser_supp(t_cmd **lst, t_list *node, t_list *lst_env, int len)
{
	int		i;
	int		check;
	t_cmd	*cmd;

	cmd = *lst;
	i = -1;
	while (node && i++ < len)
	{
		check = 0;
		cmd[i] = get_args(node, len);
		cmd[i].herdoc = read_herdocs(node, lst_env);
		while (1)
		{
			check = parser_supp1(lst, node, lst_env, i);
			if (check == -1)
				return(1);
			else if (check == 1)
				break ;
			node = node->next;
		}
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	return (0);
}

t_cmd	*parser(t_list *list, t_list *lst_env)
{
	int		len;
	t_cmd	*cmd;
	t_list	*node;

	len = get_cmd_line(list);
	cmd = malloc(sizeof(t_cmd) * len);
	node = list;
	if(parser_supp(&cmd, node, lst_env, len))
		return (NULL);
	ft_lstclear(&list, ft_del);
	return (cmd);
}
