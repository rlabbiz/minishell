/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/02 15:03:44 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char *prompt;;
	char *line;
	prompt = ft_strdup("minishell$ ");
	line = readline(prompt);
	while (line[0] == '\0')
	{
		free(line);
		line = readline(prompt);
	}
	free(prompt);
	return (line);
}

int main(void)
{
	char *line;
	t_list *list;
	t_cmd *cmd;
	
	line = get_line();
	while (line != NULL)
	{ 
		list = NULL;
		add_history(line);
		split_cmd(line, &list);
		free(line);
		if (!check_node(list))
		{
			cmd = parser(list);
			if (cmd)
				print(cmd);
		}
		line = get_line();
	}
	return (0);
}
