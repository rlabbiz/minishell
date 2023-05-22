/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/20 15:11:21 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	char *prompt;
	char **cmd;
	t_list list;

	prompt = ft_strdup("minishell$ ");
	line = readline(prompt);
	while (line != NULL)
	{
		add_history(line);
		cmd = split_cmd(line, &list);
		free(cmd);
		free(line);
		line = readline(prompt);
	}
	return (0);
}
