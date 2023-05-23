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

void ft_del(void *pointer)
{
	free(pointer);
}

int main(void)
{
	char *line;
	char *prompt;
	t_list *list;

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
			// parser(list, command);
		}
		line = readline(prompt);
	}
	free(prompt);
	return (0);
}
