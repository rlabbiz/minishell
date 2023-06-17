/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:45:45 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/17 20:02:33 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_supp(t_list *lst_env, char *herdoc, int fd, int expand)
{
	if (expand == 0)
	{
		ft_putstr_fd(herdoc, fd);
		ft_putstr_fd("\n", fd);
	}
	else if (expand == 1)
		write_expantion(lst_env, herdoc, fd);
}

int	herdoc(char *file, t_list *lst_env, int expand)
{
	int		fd[2];
	char	*herdoc;
	if (pipe(fd) == -1)
		exit(1);
	herdoc = readline("> ");
	while (herdoc)
	{
		if (ft_strncmp(herdoc, file, ft_strlen(file)) == 0
			&& ft_strlen(herdoc) == ft_strlen(file))
			break ;
		else
			herdoc_supp(lst_env, herdoc, fd[1], expand);
		free(herdoc);
		herdoc = readline("> ");
	}
	close(fd[1]);
	if (herdoc)
		free(herdoc);
	return (fd[0]);
}

int	read_herdocs(t_list *lst, t_list *lst_env)
{
	t_list	*node;
	int		fd;
	int		expand;

	node = lst;
	fd = -1;
	expand = 1;
	while (node && node->next && !check_pipe(node->content, 0))
	{
		if (check_rdr(node->content) == RDR_HERDOC)
		{
			node = node->next;
			if (ft_strchr(node->content, '\'')
				|| ft_strchr(node->content, '\"'))
				expand = 0;
			else
				expand = 1;
			if (fd != -1)
				close(fd);
			fd = herdoc(check_cmd(node->content), lst_env, expand);
		}
		node = node->next;
	}
	return (fd);
}