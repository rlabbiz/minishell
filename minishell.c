/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/31 15:30:07 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"


void print_stack(t_list *node)
{
	t_list *list = node;
	while (list != NULL)
	{
		printf(" ====> (%s)\n", list->content);
		list = list->next;
	}
}

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
		printf("-	ofd: %d\t\t\t\t-\n", cmd[i].ofd);
		printf("-	ifd: %d\t\t\t\t-\n", cmd[i].ifd);
		printf("-	inred: %d\t\t\t-\n", cmd[i].inred);
		printf("-	outred: %d\t\t\t-\n", cmd[i].outred);
		printf("-	cmd_len: %d\t\t\t-\n", cmd[i].cmd_len);
		printf("-----------------------------------------\n");
		i++;
	}
}

int main(void)
{
	char *line;
	char *prompt;
	t_list *list;
<<<<<<< HEAD
	t_cmd *cmd = NULL;
=======
	// t_list *new = NULL;
	// t_cmd *cmd = NULL;

	prompt = ft_strdup("minishell$ ");
	
	line = readline(prompt);
	while (line[0] == '\0')
	{
		free(line);
		line = readline(prompt);
	}
	while (line != NULL)
	{ 
		list = NULL;
		add_history(line);
		split_cmd(line, &list);
		free(line);
		if (!check_node(list))
		{
			print_stack(list);
			// new = parser(&list, &cmd);
			// print(new);
		}
		line = readline(prompt);
		while (line[0] == '\0')
		{
			free(line);
			line = readline(prompt);
		}
	}
	free(prompt);
	return (0);
}
