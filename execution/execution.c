/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/12 20:33:00 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

*/

void echo(char **args, int type, int fd)
{
	int	i;
	int	check;

	(void)type;
	(void)fd;
	if (args[0] && !ft_strncmp(args[0], "-n", 2) && ft_strlen(args[0]) == 2)
	{
		i = 1;
		check = 0;
	}
	else
	{
		i = 0;
		check = 1;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (check)
		printf("\n");
}

void pwd(t_list *env)
{
	printf("%s\n", get_env_value(env, "PWD"));
}

void env(t_cmd cmd, t_list **lst_env)
{
	if (cmd.args[1] != NULL)
		printf("env: %s: No such file or directory\n", cmd.args[1]);
	else
		print_env(*lst_env);
}
void export(t_cmd cmd, t_list **lst_env)
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
			return ;
		export_env(lst_env, cmd.args[i]);
	}
	else
		printf("export error\n");	
}

void unset(t_cmd cmd, t_list **lst_env)
{
	int	i;
	i = 1;
	while (cmd.args[i])
	{
		unset_env(lst_env, cmd.args[i]);
		i++;
	}
}

int buildtins(t_cmd *cmd, t_list **lst_env)
{
	if (!ft_strncmp(cmd->args[0], "env", 3) && ft_strlen(cmd->args[0]) == 3)
		env(*cmd, lst_env);
	else if (!ft_strncmp(cmd->args[0], "export", 6) && ft_strlen(cmd->args[0]) == 6)
		export(*cmd, lst_env);
	else if (!ft_strncmp(cmd->args[0], "unset", 5) && ft_strlen(cmd->args[0]) == 5)
		unset(*cmd, lst_env);
	else if (!ft_strncmp(cmd->args[0], "echo", 4) && ft_strlen(cmd->args[0]) == 4)
		echo((*cmd).args + 1, 0 ,0);
	else if (!ft_strncmp(cmd->args[0], "exit", 4) && ft_strlen(cmd->args[0]) == 4)
		exit(0);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3) && ft_strlen(cmd->args[0]) == 3)
		pwd(*lst_env);
	return (0);
}

int not_buildtins_cmd(t_cmd *cmd, t_list **lst_env)
{
	(void)cmd;
	(void)lst_env;
	return (1);
}

void	one_cmd(t_cmd *cmd, t_list **lst_env)
{
	if (!cmd->args || !cmd->args[0])
		return ;
	// cmd->args = expand(cmd->args, *);
	if (buildtins(cmd, lst_env) || not_buildtins_cmd(cmd, lst_env))
		return ;
}

void multi_cmd(t_cmd *cmd, t_list **lst_env)
{
	int	i;
	int len;

	i = 0;
	len = cmd[0].cmd_len;
	while (i < len)
	{
		// buildtins(cmd[i], lst_env);
		i++;
	}
	buildtins(&cmd[len - 1], lst_env);
}

void execution(t_cmd *cmd, t_list **lst_env)
{
	int	len;

	if (!cmd || !lst_env)
		return ;
	len = cmd[0].cmd_len;
	if (len == 1)
		one_cmd(&cmd[0], lst_env);
	else if (len > 1)
		multi_cmd(cmd, lst_env);
	// free(cmd);
	// ft_lstclear(&lst_env, del_env);
}

