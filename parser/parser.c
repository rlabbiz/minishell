/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/07 19:34:42 by rlabbiz          ###   ########.fr       */
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
			cmd.args[i] = check_cmd_and_expand(node->content);
			i++;
			node = node->next;
		}
	}
	cmd.args[i] = NULL;
	cmd.ifd = NONE;
	cmd.ofd = NONE;
	cmd.inred = NONE;
	cmd.outred = NONE;
	cmd.herdoc = NONE;
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

int  redirections(t_cmd *cmd, char *file, int rdr)
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
		else if (access(file, R_OK) == -1)
		{
			printf("bash: %s: Permission denied\n", file);
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
		cmd->outred = cmd->herdoc;
		cmd->herdoc = 0;
	}
	return (0);
}

int ft_charlen(char *str, int c)
{
	int i = 0;
	int len = 0;	
	while (str && str[i])
	{
		if (str[i] == c)
			len++;
		i++;
	}
	return (len);
}

void write_expantion(t_list *lst_env, char *herdoc, int fd)
{
	char	*line;
	char	*name;
	char	*env;
	int		i;
	
	line = herdoc;
	i = 0;
	while (*line && line[i])
	{
		i = 0;
		if (*line != '$')
		{
			ft_putchar_fd(*line, fd);
			printf("%c", *line);
			line++;
		}
		else if (*line == '$')
		{
			while (line[i] && line[i] == '$')
				i++;
			if (i > 1)
			{
				if (i % 2 != 0)
				{
					ft_putchar_fd(*line, fd);
					printf("$\n");
				}
			}
			else
			{
				line++;
				while (line[i] && ft_isalnum(line[i]) && line[i] != ' ')
					i++;
				if (i == 1)
				{
					ft_putchar_fd(*line, fd);
					printf("$\n");
				}
				else
				{
					name = ft_substr(line, 0, i);
					printf("%d\n", i);
					printf("*%s*\n", name);
					env = get_env_value(lst_env, name);
					if (env)
					{
						ft_putstr_fd(env, fd);
						printf("%s\n", env);
					}
				}
			}
		}
		line = line + i;
		i = 0;
	}
}

int herdoc(char *file, t_list *lst_env, int expand)
{
	int fd[2];
	char *herdoc;
	(void)lst_env;
	if (pipe(fd) == -1)
		exit(1);
	herdoc = get_herdoc();
	while (herdoc)
	{
		if (ft_strncmp(herdoc, file, ft_strlen(file)) == 0 && ft_strlen(herdoc) == ft_strlen(file))
			break ;
		else 
		{
			if (expand == 0)
			{
				ft_putstr_fd(herdoc, fd[1]);
				printf("%s\n", herdoc);
				ft_putstr_fd("\n", fd[1]);
			}
			else if (expand == 1)
				write_expantion(lst_env, herdoc, fd[1]);
		}
			free(herdoc);
		herdoc = get_herdoc();
	}
	close(fd[1]);
	if (herdoc)
		free(herdoc);
	return (fd[0]);
}

int read_herdocs(t_list *lst, t_list *lst_env)
{
	t_list *node = lst;
	int fd = -1;
	int expand = 1;
	while (node && node->next && !check_pipe(node->content, 0))
	{
		if (check_rdr(node->content) == RDR_HERDOC)
		{
			node = node->next;
			if (ft_strchr(node->content, '\'') || ft_strchr(node->content, '\"'))
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

t_cmd *parser(t_list *list, t_list *lst_env)
{
	int len = get_cmd_line(list);
	int i = 0;
	int rdr = 0;
	t_cmd *cmd = malloc(sizeof(t_cmd) * len);
	t_list *node = list;
	(void)lst_env;
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
				if (redirections(&cmd[i], node->next->content, rdr))
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