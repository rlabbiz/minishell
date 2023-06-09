/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:44:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/09 12:56:33 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_espace(char c, int quotes)
{
	if (c != '\0' && quotes == 0 && (c == ' ' || c == '\t'))
		return (1);
	return (0);
}

char	*check_cmd(char *old_cmd)
{
	char	*new_cmd;
	int		i;
	int		j;
	int		quotes;

	new_cmd = malloc(sizeof(char ) * ft_strlen(old_cmd) + 1);
	i = 0;
	j = 0;
	quotes = 0;
	while (old_cmd[i] != '\0')
	{
		if (find_quotes(old_cmd, i, &quotes) == 1)
		{
			new_cmd[j] = old_cmd[i];
			j++;
		}
		i++;
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

int	check_if_redirections(char *c, int i, int quotes)
{
	if (quotes == 0 && (c[i] == 60 || c[i] == 62 || c[i] == '|'))
		return (1);
	return (0);
}

void	split_cmd(char *input, t_list **list)
{
	int		i;
	int		quotes;
	int		start;
	char	*cmd;
	char	c;

	if (!input)
		return ;
	i = 0;
	quotes = 0;
	start = 0;
	while (input[i] != '\0')
	{
		while (check_espace(input[i], quotes))
			i++;
		if (!input[i])
			break ;
		start = i;
		while (input[i] != '\0' && !check_espace(input[i], quotes)
			&& !check_if_quotes(input, i, &quotes)
			&& !check_if_redirections(input, i, quotes))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			i++;
		cmd = ft_substr(input, start, i - start);
		if (cmd != NULL)
			ft_lstadd_back(list, ft_lstnew(cmd));
		if (ft_strchr("<>|", input[i]))
		{
			start = i;
			c = input[i];
			while (input[i] != '\0' && ft_strchr(&c, input[i]))
				i++;
			cmd = ft_substr(input, start, i - start);
			if (cmd != NULL)
				ft_lstadd_back(list, ft_lstnew(cmd));
		}
	}
}
