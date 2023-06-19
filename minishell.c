/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/19 15:49:41 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// g_global global;

void	ft_del(void *data)
{
	free(data);
}

int ft_check_command(char *path, char *line)
{
	char *command;

	command = ft_strjoin(path, line);
	if (access(command, F_OK) == 0)
	{
		free(command);
		return (1);
	}
	free(command);
	return (0);
}

void ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = cmd[0].cmd_len;
	while (i < len)
	{
		ft_free_split(cmd[i].args);
		i++;
	}
	free(cmd);
}

void ft_free_env(void *data)
{
	t_env *env = data;
	free(env->name);
	free(env->value);
	free(env);
}

void print(t_cmd *cmd)
{
	int i = 0;
	int j = 0;
	int len = cmd[0].cmd_len;
	while (i < len)
	{
		printf("--------	command %d	---------\n", i + 1);
		printf("-	args:\t\t\t\t-\n");
		j = 0;
		while (cmd[i].args[j] != NULL)
		{
			printf("--  		%s\t\t\t-\n", cmd[i].args[j]);
			j++;
		}
		printf("-	ifd: %d\t\t\t\t-\n", cmd[i].ifd);
		printf("-	ofd: %d\t\t\t\t-\n", cmd[i].ofd);
		printf("-	inred: %d\t\t\t-\n", cmd[i].inred);
		printf("-	outred: %d\t\t\t-\n", cmd[i].outred);
		printf("-	herdoc: %d\t\t\t-\n", cmd[i].herdoc);
		printf("-	first_rdr: %d\t\t\t-\n", cmd[i].first_rdr);
		printf("-	cmd_len: %d\t\t\t-\n", cmd[i].cmd_len);
		printf("-----------------------------------------\n");
		i++;
	}
}

char *get_line(void)
{
	char	*prompt;
	char	*line;

	prompt = ft_strdup("minishell$ ");
	line = readline(prompt);
	if (line == NULL)
	{
		free (prompt);
		return (NULL);
	}
	while (line[0] == '\0')
	{
		free (line);
		line = readline(prompt);
		if (line == NULL)
		{
			free (prompt);
			return (NULL);
		}
	}
	free (prompt);
	return (line);
}

void handler(int sig)
{
	(void)sig;
	if (global.herdoc != -1)
	{
		close(global.herdoc);
		global.herdoc = -2;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line; // is freed
	t_list	*list; // is freed
	t_cmd	*cmd; // must free
	t_list	*lst_env; // must free

	global.herdoc = -1;
	av += ac;
	lst_env = get_env(&lst_env, env);
	line = get_line();
	signal(SIGINT, handler);
	while (line)
	{
		list = NULL;
		// cmd = NULL;
		add_history(line);
		split_cmd(line, &list);
		free(line);
		if (list)
		{
			if (!check_node(list))
			{
				cmd = parser(list, lst_env);
				ft_lstclear(&list, ft_del);
				if (cmd)
				{
					print(cmd);
					exec(cmd, &lst_env, env);
					ft_free_cmd(cmd);
				}
			}
		}
		// while (1);
		line = get_line();
	}
	// ft_lstclear(&lst_env, &ft_free_env);
	return (0);
}
