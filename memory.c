/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:09:05 by ael-amin          #+#    #+#             */
/*   Updated: 2023/05/20 15:12:41 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// int	ft_check_command(char *path, char *line)
// {
// 	char	*command;

// 	command = ft_strjoin(path, line);
// 	if (access(command, F_OK) == 0)
// 	{
// 		free(command);
// 		return (1);
// 	}
// 	free(command);
// 	return (0);
// }
