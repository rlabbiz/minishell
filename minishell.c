/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/08 11:16:54 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *str)
{
	int i = -1;
	while (str[i++]);
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	int i = 0;
	int j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int main(void)
{
	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
