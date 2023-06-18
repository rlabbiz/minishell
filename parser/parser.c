/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/18 21:26:08 by rlabbiz          ###   ########.fr       */
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

t_cmd	*parser(t_list *list, t_list *lst_env)
{
	int		len;
	int		i;
	int		rdr;
	t_cmd	*cmd;
	t_list	*node;

	len = get_cmd_line(list);
	i = 0;
	rdr = 0;
	cmd = malloc(sizeof(t_cmd) * len);
	node = list;
	while (node && i < len)
	{
		cmd[i] = get_args(node, len);
		cmd[i].herdoc = read_herdocs(node, lst_env);
		while (1)
		{
			if (check_pipe(node->content, 0))
				break ;
			rdr = check_rdr(node->content);
			if (node->next == NULL)
				break ;
			if (rdr != 0 && node->next)
			{
				if (redirections(&cmd[i], node->next->content, rdr, lst_env))
					return (NULL);
				node = node->next;
			}
			if (node->next == NULL)
				break ;
			node = node->next;
			rdr = 0;
		}
		if (node->next == NULL)
			break ;
		node = node->next;
		i++;
	}
	return (cmd);
}
