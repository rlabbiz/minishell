/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/26 15:00:05 by rlabbiz          ###   ########.fr       */
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

// void print(t_list *node)
// {


// 	while (node != NULL)
// 	{
// 		t_cmd *cmd = (t_cmd *)node->content;
// 		printf("the args is %s\nthe fd is %d\nthe type is %d\n", cmd->arg, cmd->fd, cmd->type);
// 		node = node->next;
// 	}
// }

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
>>>>>>> 07e77acae8bccc492b4dfeb08dffe616e1863d39

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
<<<<<<< HEAD
			list = parser(list, &cmd);
=======
			// new = parser(&list, &cmd);
			// print(new);
>>>>>>> 07e77acae8bccc492b4dfeb08dffe616e1863d39
		}
		line = readline(prompt);
	}
	free(prompt);
	return (0);
}
