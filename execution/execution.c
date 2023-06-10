/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/10 21:29:56 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

*/

int buildtins(t_cmd cmd, t_list **lst_env)
{
	int	i;
	
	if (!ft_strncmp(cmd.args[0], "env", 3) && ft_strlen(cmd.args[0]) == 3)
	{
        if (cmd.args[1] != NULL)
			printf("env: %s: No such file or directory\n", cmd.args[1]);
		else
			print_env(*lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd.args[0], "export", 6) && ft_strlen(cmd.args[0]) == 6)
	{
		if (cmd.args[1] != NULL)
		{
			i = 1;
			while (cmd.args[i])
			{
				if (ft_strchr(cmd.args[i], '='))
					break ;
				i++;
			}
			if (!cmd.args[i])
				return (1);
			export_env(lst_env, cmd.args[i]);
		}
		else
			printf("export error\n");
	}
	else if (!ft_strncmp(cmd.args[0], "unset", 5) && ft_strlen(cmd.args[0]) == 5)
	{
		i = 1;
		while (cmd.args[i])
		{
			unset_env(lst_env, cmd.args[i]);
			i++;
		}
		return (1);
	}
	else if (!ft_strncmp(cmd.args[0], "echo", 4) && ft_strlen(cmd.args[0]) == 4)
	{
		
	}
	return (0);
}
int not_buildtins_cmd(t_cmd cmd, t_list **lst_env)
{
	(void)cmd;
	(void)lst_env;
	return (1);
}

void	one_cmd(t_cmd cmd, t_list **lst_env)
{
	if (!cmd.args || !cmd.args[0])
		return ;
	if (buildtins(cmd, lst_env) || not_buildtins_cmd(cmd, lst_env))
		return ;
}

void execution(t_cmd *cmd, t_list **lst_env)
{
	int	len;

	if (!cmd || !lst_env)
		return ;
	len = cmd[0].cmd_len;
	if (len == 1)
		one_cmd(cmd[0], lst_env);
	// else if (len > 1)
	// 	multi_cmd(cmd, lst_env);
	// free(cmd);
	// ft_lstclear(&lst_env, del_env);
}

