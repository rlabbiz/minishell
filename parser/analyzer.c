/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:59:41 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/22 18:19:01 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*

void check_node(node)
    if (check_pipe(node->data))
        print "bash: syntax error near unexpected token '|'"
        ft_free(&node)
        return
    check_quotes_and_remove(node)
    while (node != NULL)
        if (check_syntax(node))
            ft_free(&node)
            return
        node = node->next

int check_pipe(data, first)
    if (first == 1 and *data == |)
        return 1
    if (first == 0 and *data == | and ft_strlen(data) != 1)
        return 1
    return 0

int check_rdr(data)
    if (*data == < || *data == >)
		if (!ft_strncmp(data, <) and ft_strlen(data) == 1)
			return 1
		else if (!ft_strcmp(data, >) and ft_strlen(data) == 1)
			return 1
		else if (!ft_strcmp(dara, >>) and ft_strlen(data) == 2)
			return 1
		else if (!ft_strcmp(data, <<) and ft_strlen(data) == 2)
		else if (ft_strlen(data) == 3)
			print "bash: syntax error near unexpected token `*data'"
		else if (ft_strlen(data) > 3)
			print "bash: syntax error near unexpected token `*data *data'"
    return 0

int syntax_error(node)
    if (check_rdr(node->data)) and!node-next)
		print "minishell: syntax error near unexpected token `newline'"
        return 1
	if (check_pipe(node->data) and !node->next)
		print "minishell: syntax error near unexpected token `|'"
    	return 1
	if (check_rdr(node->data) && check_rdr(node->next->data))
		if (ft_strlen(node->next->data) == 1)
			print "bash: syntax error near unexpected token `*data'"
			return 1
		else if (ft_strlen(node->next->data) > 1)
			print "bash: syntax error near unexpected token `*data *data'"
			return 1
	else if (check_rdr(node->data) && check_pipe(node->next->data))
		print "bash: syntax error near unexpected token `|'"
		return 1
	return 0

*/

int check_pipe(char *data, int first)
{
    if (first == 1 && data[0] == '|')
    {
        printf("minishell: syntax error near unexpected token '|'\n");
        return (-1);
    }
    if (first == 0 && data[0] == '|' && ft_strlen(data) != 1)
    {
        printf("minishell: syntax error near unexpected token '|'\n");
        return (-1);
    }
	if (first == 0 && data[0] == '|' && ft_strlen(data) == 1)
		return (1);
    return (0);
}

int rdr_error(char *data)
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
		printf("minishell: syntax error near unexpected token `%c%c'\n", data[0], data[0]);
		return (1);
	}
	return (0);
}

int check_rdr(char *data)
{
	if (data[0] != '<' && data[0] != '>')
		return (0);
	if (ft_strlen(data) == 1 && !ft_strncmp(data, "<", 1))
		return (1);
	else if (ft_strlen(data) == 1 && !ft_strncmp(data, ">", 1))
		return (1);
	else if (ft_strlen(data) == 2 && !ft_strncmp(data, "<<", 2))
		return (1);
	else if (ft_strlen(data) == 2 && !ft_strncmp(data, ">>", 2))
		return (1);
    return (0);
}

int syntax_error(t_list *list)
{
	t_list *node = list;
	
	if (check_pipe(node->content, 0) == -1 || rdr_error(node->content))
		return (1);
	if (check_rdr(node->content) && node->next == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (check_pipe(node->content, 0) && node->next == NULL)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (check_rdr(node->content) && check_rdr(node->next->content))
	{
		if (ft_strlen(node->next->content) == 1)
		{
			printf("bash: syntax error near unexpected token `%c'\n", node->next->content[0]);
			return (1);
		}
		else if (ft_strlen(node->next->content) > 1)
		{
			printf("bash: syntax error near unexpected token `%c%c'\n", node->next->content[0], node->next->content[0]);
			return (1);
		}
	}
	else if (check_rdr(node->content) && check_pipe(node->next->content, 0))
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int check_node(t_list *list)
{
    t_list *node = list;
    if (check_pipe(node->content, 1) == -1)
	{
		ft_lstclear(&list, &ft_del);
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
