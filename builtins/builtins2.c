/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:20:59 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/19 17:21:51 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(t_cmd cmd, t_list **lst_env)
{
	if (cmd.args[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd.args[1]);
		return (1);
	}
	else
		print_env(*lst_env);
	return (0);
}

int	exec_export(t_cmd cmd, t_list **lst_env)
{
	int	i;

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
		add_var_to_env(lst_env, cmd.args[i]);
	}
	else
	{
		printf("export error\n");
		return (1);
	}
	return (0);
}

int	exec_unset(t_cmd cmd, t_list **lst_env)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		unset_env(lst_env, cmd.args[i]);
		i++;
	}
	return (0);
}
