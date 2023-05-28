/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/23 13:15:27 by rlabbiz          ###   ########.fr       */
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

int main(void)
{
	char *line;
	char *prompt;
	t_list *list;
	t_cmd *cmd = NULL;

	prompt = ft_strdup("minishell$ ");
	line = readline(prompt);
	while (line != NULL)
	{
		list = NULL;
		add_history(line);
		split_cmd(line, &list);
		free(line);
		if (!check_node(list))
		{
			print_stack(list);
			list = parser(list, &cmd);
		}
		line = readline(prompt);
	}
	free(prompt);
	return (0);
}
