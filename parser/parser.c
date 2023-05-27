/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/26 18:03:56 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

struct t_cmd
    char *arg;
    int fd;
    int type;

struct t_list
    void *content;
    t_list *next;

t_cmd *parser(t_list *node)
	t_cmd *cmd = malloc(sizeof(t_cmd) * len);
	cmd->arg = malloc(sizeof(char *) * (len + 1))
	int i = 0;
	if (ft_strncmp(node->content, ">", 1) == 0 && ft_strlen(node->content) == 1)
	{
		ft_redirection(&cmd, node->next->content, ">");
		node = node->next->next;
	}
	else if (ft_strncmp(node->content, "<", 1) == 0 && ft_strlen(node->content) == 1)
	{
		ft_redirection(&cmd, node->next->content, ">");
		node = node->next->next;
	}
	else if (ft_strncmp(node->content, ">>", 2) == 0 && ft_strlen(node->content) == 2)
	{
		ft_redirection(&cmd, node->next->content, ">>");
		node = node->next->next;
	}
	else if (ft_strncmp(node->content, "<<", 2) == 0 && ft_strlen(node->content) == 2)
	{
		ft_redirection(&cmd, node->next->content, "<<");
		node = node->next->next;
	}
	else if (ft_strncmp(node->content, "|") == 0 && ft_strlen(node->content) == 1)
	{
		ft_pipe(&cmd, list);
		node = node->next->next;
	}
	else
	{
		while (check_rdr_pipe(node))
		{
			cmd->arg = arrayjoin(cmd->arg, node->content);
			node = node->next;
		}
	}
	
	return (cmd);
*/

int get_cmd_line(t_list *list)
{
    t_list *node = list;
    int len = 0;
    while (node != NULL)
    {
        if (!ft_strncmp((char *)node->content, "|", 1) && ft_strlen((char *)node->content) == 1)
            len++;
        node = node->next;
    }
    return (len + 1);
}

t_cmd get_cmd(t_list *list)
{
	
}

t_list *parser(t_list *list)
{
	int len = get_cmd_line(list);
	int i = 0;
	t_cmd *cmd = malloc(sizeof(t_cmd) * len);
	t_list *node = list;
	while (i < len)
	{
		cmd[i] = get_cmd(node);
		i++;
	}
}