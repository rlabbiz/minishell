/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excuetion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/08 15:11:07 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void excuetion(t_cmd *cmd, t_list *lst_env)
{
    int i;
    int len;

    i = 0;
    len = cmd[0].cmd_len;
    while (i < len)
    {
        if (cmd[i].args && cmd[i].args[0])
        {
            if (!ft_strncmp(cmd[i].args[0], "env", 3) && ft_strlen(cmd[i].args[0]) == 3)
                print_env(lst_env);
            
        }
        i++;
    }
}