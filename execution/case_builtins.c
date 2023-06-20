/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:43 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/19 18:05:46 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		return (1);
	return (0);
}

int	part1(t_cmd *cmd, t_list **lst_env)
{
	if (!ft_strncmp(cmd->args[0], "cd", 2) && ft_strlen(cmd->args[0]) == 2)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "echo", 4)
		&& ft_strlen(cmd->args[0]) == 4)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "export", 6)
		&& ft_strlen(cmd->args[0]) == 6)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	return (0);
}

int part2(t_cmd *cmd, t_list **lst_env)
{
	if (!ft_strncmp(cmd->args[0], "env", 3)
		&& ft_strlen(cmd->args[0]) == 3)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "unset", 5)
		&& ft_strlen(cmd->args[0]) == 5)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "exit", 4)
		&& ft_strlen(cmd->args[0]) == 4)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	return (0);
}

int	cmd_in_parent(t_cmd *cmd, t_list **lst_env)
{
	if (part1(cmd, lst_env))
		return (1);
	else if (part2(cmd, lst_env))
		return (1);
	return (0);
}
