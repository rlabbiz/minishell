/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:59:41 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/10 13:13:59 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *data, int first)
{
	if (first == 1 && data[0] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if ((first == 0 || first == -1) && data[0] == '|' && ft_strlen(data) != 1)
	{
		if (first == 0)
			printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	if (first == 0 && data[0] == '|' && ft_strlen(data) == 1)
		return (1);
	return (0);
}

int	rdr_error(char *data)
{
	if (data[0] != '<' && data[0] != '>')
		return (0);
	if (ft_strlen(data) == 3)
	{
		printf("minishell: syntax error near unexpected token `%c'\n", data[0]);
		return (1);
	}
	else if (ft_strlen(data) > 3)
	{
		printf("minishell: syntax error near unexpected token `%c%c'\n",
			data[0], data[0]);
		return (1);
	}
	return (0);
}

int	check_rdr(char *data)
{
	if (data[0] != '<' && data[0] != '>')
		return (0);
	if (ft_strlen(data) == 1 && !ft_strncmp(data, "<", 1))
		return (RDR_OUT);
	else if (ft_strlen(data) == 1 && !ft_strncmp(data, ">", 1))
		return (RDR_IN);
	else if (ft_strlen(data) == 2 && !ft_strncmp(data, "<<", 2))
		return (RDR_HERDOC);
	else if (ft_strlen(data) == 2 && !ft_strncmp(data, ">>", 2))
		return (RDR_APPEND);
	return (0);
}

int	syntax_error(t_list *list)
{
	t_list	*node;

	node = list;
	if (check_pipe(node->content, 0) == -1 || rdr_error(node->content))
		return (1);
	else if (check_rdr(node->content) && node->next == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (check_pipe(node->content, 0) && node->next == NULL)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (check_rdr(node->content) && check_rdr(node->next->content))
	{
		if (ft_strlen(node->next->content) == 1)
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				((char *)node->next->content)[0]);
			return (1);
		}
		else if (ft_strlen(node->next->content) > 1)
		{
			printf("minishell: syntax error near unexpected token `%c%c'\n",
				((char *)node->next->content)[0],
				((char *)node->next->content)[0]);
			return (1);
		}
	}
	else if (check_rdr(node->content) && check_pipe(node->next->content, -1))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	check_node(t_list *list)
{
	t_list	*node;

	node = list;
	if (check_pipe(node->content, 1) == -1)
	{
		ft_lstclear(&list, ft_del);
		return (1);
	}
	while (node != NULL)
	{
		if (syntax_error(node) || check_quotes(node->content))
		{
			ft_lstclear(&list, &ft_del);
			return (1);
		}
		node = node->next;
	}
	return (0);
}
