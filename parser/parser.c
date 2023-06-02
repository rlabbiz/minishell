/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/01 17:02:21 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

t_cmd *parser(t_list *node)
	t_cmd *cmd = malloc(sizeof(t_cmd) * len);
	while (node != NULL AND i < len)
	{
		cmd[i] = get_args(node, len);
		while (1)
		{
			if (check_pipe(node) OR node == NULL)
				break ;
			rdr = check_rdr(node->content);
			if (rdr != 0 AND node->next != NULL)
				redirections(&cmd[i], node->next->content, rdr);
				node = node->next;
			node = node->next;
			rdr = 0;
		}
		node = node->next;
		i++;
	}
	return (cmd);

t_cmd get_args(t_list *node, int cmd_len)
	while (node != NULL AND !check_pipe(node->content, 0))
		if (node->next != NULL AND check_rdr(node->content) != 0)
			node = node->next->next;
		if (node != NULL AND !check_pipe(node->content) AND !check_rdr(node->content))
			len++;
			node = node->next;

	cmd->args = malloc(sizeof(char *) * (i + 1));
	while (node != NULL AND i < len AND !check_pipe(node->content, 0))
		if (node->next != NULL AND check_rdr(node->content) != 0)
			node = node->next->next;
		if (node != NULL AND !check_pipe(node->content) AND !check_rdr(node->content))
			cmd->args[i] = check_cmd(node->content);
			i++;
			node = node->next;
	cmd->args[i] = NULL;
	cmd->ifd = NONE;
	cmd->ofd = NONE;
	cmd->inred = NONE;
	cmd->outred = NONE;
	cmd->cmd_len = cmd_len;
	
*/

int get_cmd_line(t_list *list)
{
    t_list *node = list;
    int len = 0;
    while (node != NULL)
    {
        if (!ft_strncmp((char *)node->content, "|", 1) && ft_strlen((char *)node->content) == 1)
            len++;
        node = node->next;
    }
    return (len + 1);
}

t_cmd get_args(t_list *lst, int cmd_len)
{
	t_cmd cmd;
	t_list *node = lst;
	int len = 0;
	int i = 0;

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
	node = lst;
	cmd.args = malloc(sizeof(char *) * (len + 1));
	while (node && i < len && !check_pipe(node->content, 0))
	{
		if (node->next != NULL && check_rdr(node->content) != 0)
			node = node->next->next;
		if (!node)
			break ;
		if (node && !check_pipe(node->content, 0) && !check_rdr(node->content))
		{
			cmd.args[i] = check_cmd(node->content);
			i++;
			node = node->next;
		}
	}
	cmd.args[i] = NULL;
	cmd.ifd = NONE;
	cmd.ofd = NONE;
	cmd.inred = NONE;
	cmd.outred = NONE;
	cmd.first_rdr = NONE;
	cmd.cmd_len = cmd_len;
	return (cmd);
}

char *get_herdoc(void)
{
	char *herdoc;

	herdoc = readline("> ");
	while (herdoc[0] == '\0')
		herdoc = readline("> ");
	return (herdoc);
}

int herdoc(char *file)
{
	int fd[2];
	char *herdoc;
	if (pipe(fd) == -1)
		exit(1);
	herdoc = get_herdoc();
	while (herdoc)
	{
		if (ft_strncmp(herdoc, file, ft_strlen(file)) == 0 && ft_strlen(herdoc) == ft_strlen(file))
			break ;
		ft_putstr_fd(herdoc, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(herdoc);
		herdoc = get_herdoc();
	}
	close(fd[1]);
	if (herdoc)
		free(herdoc);
	return (fd[0]);
}

int  redirections(t_cmd *cmd, char *file, int rdr, int *fd)
{
	if (rdr == RDR_IN)
	{
		if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_APPEND)
			cmd->first_rdr = RDR_IN;
		if (cmd->ifd != NONE)
			close(cmd->ifd);
		if (cmd->inred != NONE)
		{
			close(cmd->inred);
			cmd->inred = NONE;
		}
		cmd->ifd = open(file, O_WRONLY | O_TRUNC | O_CREAT);
	}
	else if (rdr == RDR_OUT)
	{
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
		cmd->ofd = open(file, O_RDONLY);
	}
	else if (rdr == RDR_APPEND)
	{
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
	}
	else if (rdr == RDR_HERDOC)
	{
		if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_OUT)
			cmd->first_rdr = RDR_HERDOC;
		if (cmd->outred != NONE)
			close(cmd->outred);
		if (cmd->ofd != NONE)
		{
			close(cmd->ofd);
			cmd->ofd = NONE;
		}
		cmd->outred = herdoc(file);
	}
	return (0);
}

t_cmd *parser(t_list *list)
{
	int len = get_cmd_line(list);
	int i = 0;
	int rdr = 0;
	int fd = 0;
	t_cmd *cmd = malloc(sizeof(t_cmd) * len);
	t_list *node = list;
	while (node && i < len)
	{
		cmd[i] = get_args(node, len);
		while (1)
		{
			if (check_pipe(node->content, 0))
				break ;
			rdr = check_rdr(node->content);
			if (node->next == NULL)
				break ;
			if (rdr != 0 && node->next)
			{
				if (redirections(&cmd[i], node->next->content, rdr, &fd))
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
