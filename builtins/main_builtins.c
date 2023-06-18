/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_principal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:29:56 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/18 21:30:26 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(t_cmd *cmd, t_list **lst_env)
{
	if (!ft_strncmp(cmd->args[0], "env", 3) && ft_strlen(cmd->args[0]) == 3)
		exec_env(*cmd, lst_env);
	else if (!ft_strncmp(cmd->args[0], "export", 6)
		&& ft_strlen(cmd->args[0]) == 6)
		exec_export(*cmd, lst_env);
	else if (!ft_strncmp(cmd->args[0], "unset", 5)
		&& ft_strlen(cmd->args[0]) == 5)
		exec_unset(*cmd, lst_env);
	else if (!ft_strncmp(cmd->args[0], "echo", 4)
		&& ft_strlen(cmd->args[0]) == 4)
		exec_echo((*cmd).args + 1, 0 ,0);
	else if (!ft_strncmp(cmd->args[0], "exit", 4)
		&& ft_strlen(cmd->args[0]) == 4)
		exit(0);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3)
		&& ft_strlen(cmd->args[0]) == 3)
		exec_pwd(*lst_env);
	else if (!ft_strncmp(cmd->args[0], "cd", 2) && ft_strlen(cmd->args[0]) == 2)
		exec_cd(*cmd, *lst_env);
	return (0);
}
