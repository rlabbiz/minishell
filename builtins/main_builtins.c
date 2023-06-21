/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:29:56 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/21 16:01:38 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(t_cmd *cmd, t_list **lst_env)
{
	if (!ft_strncmp(cmd->args[0], "env", 3) && ft_strlen(cmd->args[0]) == 3)
		return (exec_env(*cmd, lst_env));
	else if (!ft_strncmp(cmd->args[0], "export", 6)
		&& ft_strlen(cmd->args[0]) == 6)
		return (exec_export(*cmd, lst_env));
	else if (!ft_strncmp(cmd->args[0], "unset", 5)
		&& ft_strlen(cmd->args[0]) == 5)
		return (exec_unset(*cmd, lst_env));
	else if (!ft_strncmp(cmd->args[0], "echo", 4)
		&& ft_strlen(cmd->args[0]) == 4)
		return (exec_echo((*cmd).args + 1, 0 ,0));
	else if (!ft_strncmp(cmd->args[0], "exit", 4)
		&& ft_strlen(cmd->args[0]) == 4)
		return (exit(0), 0);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3)
		&& ft_strlen(cmd->args[0]) == 3)
		return (exec_pwd(*lst_env));
	else if (!ft_strncmp(cmd->args[0], "cd", 2) && ft_strlen(cmd->args[0]) == 2)
		return (exec_cd(*cmd, *lst_env));
	return (0);
}
