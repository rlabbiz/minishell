/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/23 14:38:27 by rlabbiz          ###   ########.fr       */
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

t_list *parser(t_list *node)
    t_cmd *cmd;
    len = get_cmd_len(node);
    cmd = malloc(sizeof(t_cmd) * len);
    while (i < len)
        if ((char *)(node->content)[0] == <)
            if (&& ft_strlen(node->content) == 1)
                cmd[i].type = RDR_OUT;
                cmd[i].fd = rdr_out((char *)node->next->content);
            else if (&& ft_strlen(node->content) == 2)
                cmd[i].type = RDR_HERDOCT;
                cmd[i].fd = rdr_herdoct((char *)node->next->content);
        else if ((char *)(node->content)[0] == >)  
            if (ft_strlen(node->content) == 1)
                cmd[i].type = RDR_IN;
                cmd[i].fd = rdr_in((char *)node->next->content);
            else if (ft_strlen(node->content) == 2)
                cmd[i].type = RDR_APPEND;
                cmd[i].fd = rdr_append((char *)node->next->content);
        else if ((char *)(node->content)[0] == | )
            i++;
        else
            cmd[i].arg = (char *)node->content;
        node = node->next;

*/