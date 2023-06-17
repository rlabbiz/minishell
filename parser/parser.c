/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/17 17:27:07 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cmd_line(t_list *list)
{
	t_list	*node;
	int		len;

	len = 0;
	node = list;
	while (node != NULL)
	{
		if (!ft_strncmp((char *)node->content, "|", 1)
			&& ft_strlen((char *)node->content) == 1)
			len++;
		node = node->next;
	}
	return (len + 1);
}

void	get_arrgs_supp(t_list *node, t_cmd *cmd, int len, int cmd_len)
{
	int	i;

	i = 0;
	cmd->args = malloc(sizeof(char *) * (len + 1));
	while (node && i < len && !check_pipe(node->content, 0))
	{
		if (node->next != NULL && check_rdr(node->content) != 0)
			node = node->next->next;
		if (!node)
			break ;
		if (node && !check_pipe(node->content, 0) && !check_rdr(node->content))
		{
			cmd->args[i] = ft_strdup(node->content);
			i++;
			node = node->next;
		}
	}
	cmd->args[i] = NULL;
	cmd->ifd = NONE;
	cmd->ofd = NONE;
	cmd->inred = NONE;
	cmd->outred = NONE;
	cmd->herdoc = NONE;
	cmd->first_rdr = NONE;
	cmd->cmd_len = cmd_len;
}

t_cmd	get_args(t_list *lst, int cmd_len)
{
	t_cmd	cmd;
	t_list	*node;
	int		len;
	int		i;

	node = lst;
	len = 0;
	i = 0;
	while (node && !check_pipe(node->content, 0))
	{
		if (node->next && check_rdr(node->content) != 0)
			node = node->next->next;
		if (!node)
			break ;
		if (check_pipe(node->content, 0))
			break ;
		if (node && !check_rdr(node->content))
		{
			len++;
			node = node->next;
		}
	}
	get_arrgs_supp(lst, &cmd, len, cmd_len);
	return (cmd);
}

char	*get_herdoc(void)
{
	char	*herdoc;

	herdoc = readline("> ");
	return (herdoc);
}

int	check_onbiges(char *file)
{
	int i = 0;
	int len = 0;
	char c;

	c = 1;
	while (file[i])
	{
		if (file[i] == c)
			len++;
		i++;
	}
	if (len > 2)
		return (1);
	return (0);
}

void redirections_in(t_cmd **lst, char *file)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_APPEND)
		cmd->first_rdr = RDR_IN;
	if (cmd->ifd != NONE)
		close(cmd->ifd);
	if (cmd->inred != NONE)
	{
		close(cmd->inred);
		cmd->inred = NONE;
	}
	if (access(file, F_OK) == -1)
		cmd->ifd = open(file, O_CREAT | O_WRONLY);
	else
		cmd->ifd = open(file, O_WRONLY);
}

int redirections_out(t_cmd **lst, char *file)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_HERDOC)
		cmd->first_rdr = RDR_OUT;
	if (cmd->ofd != NONE)
		close(cmd->ofd);
	if (cmd->outred != NONE)
	{
		close(cmd->outred);
		cmd->outred = NONE;
	}
	if (access(file, F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (1);
	}
	else if (access(file, R_OK) == -1)
	{
		printf("bash: %s: Permission denied\n", file);
		return (1);
	}
	cmd->ofd = open(file, O_RDONLY);
	return (0);
}

int redirections_append(t_cmd **lst, char *file)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_IN)
		cmd->first_rdr = RDR_APPEND;
	if (cmd->inred != NONE)
		close(cmd->inred);
	if (cmd->ifd != NONE)
	{
		close(cmd->ifd);
		cmd->ifd = NONE;
	}
	if (access(file, F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (1);
	}
	cmd->inred = open(file, O_RDWR | O_CREAT | O_APPEND);
	return (0);
}

void redirections_herdoc(t_cmd **lst)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_OUT)
		cmd->first_rdr = RDR_HERDOC;
	if (cmd->outred != NONE)
		close(cmd->outred);
	if (cmd->ofd != NONE)
	{
		close(cmd->ofd);
		cmd->ofd = NONE;
	}
	cmd->outred = cmd->herdoc;
	cmd->herdoc = 0;
}

int	redirections(t_cmd *cmd, char *str, int rdr, t_list *lst_env)
{
	char *old_file = expantion(str, lst_env, 1);
	char *file;
	if (!old_file || check_onbiges(old_file))
	{
		printf("minishell: %s: ambiguous redirect\n", str);
		return(-1);
	}
	file = check_cmd(old_file);
	if (rdr == RDR_IN)
		redirections_in(&cmd, file);
	else if (rdr == RDR_OUT && redirections_out(&cmd, file))
		return (1);
	else if (rdr == RDR_APPEND && redirections_append(&cmd, file))
		return (1);
	else if (rdr == RDR_HERDOC)
		redirections_herdoc(&cmd);
	return (0);
}

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
				int check = redirections(&cmd[i], node->next->content, rdr, lst_env);
				if (check == 1 || check == -1)
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
	ft_lstclear(&list, ft_del);
	return (cmd);
}
