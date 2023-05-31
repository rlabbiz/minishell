/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/30 17:45:38 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

t_cmd *parser(t_list *node)
	t_cmd *cmd = malloc(sizeof(t_cmd) * len);
	while (node != NULL AND i < len)
	{
		cmd[i] = get_args(node, len);
		while (1)
		{
			if (check_pipe(node) OR node == NULL)
				break ;
			rdr = check_rdr(node->content);
			if (rdr != 0 AND node->next != NULL)
				redirections(&cmd[i], node->next->content, rdr);
				node = node->next;
			node = node->next;
			rdr = 0;
		}
		node = node->next;
		i++;
	}
	return (cmd);

t_cmd get_args(t_list *node, int cmd_len)
	while (node != NULL AND !check_pipe(node->content, 0))
		if (node->next != NULL AND check_rdr(node->content) != 0)
			node = node->next->next;
		if (node != NULL AND !check_pipe(node->content) AND !check_rdr(node->content))
			len++;
			node = node->next;

	cmd->args = malloc(sizeof(char *) * (i + 1));
	while (node != NULL AND i < len AND !check_pipe(node->content, 0))
		if (node->next != NULL AND check_rdr(node->content) != 0)
			node = node->next->next;
		if (node != NULL AND !check_pipe(node->content) AND !check_rdr(node->content))
			cmd->args[i] = check_cmd(node->content);
			i++;
			node = node->next;
	cmd->args[i] = NULL;
	cmd->ifd = NONE;
	cmd->ofd = NONE;
	cmd->inred = NONE;
	cmd->outred = NONE;
	cmd->cmd_len = cmd_len;
	
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