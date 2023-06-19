/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:10:03 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/18 22:49:01 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_echo(char **args, int type, int fd) // khasha un case
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
	return (0);
}

int	exec_cd(t_cmd cmd, t_list *list_env)
{
	char	*home;

	home = get_env_value(list_env, "HOME");
	if (cmd.args[1] == NULL)
	{
		if (home == NULL)
		{
			printf("cd : Unable to retrieve home directory\n"); /* doubt */
			return (1);
		}
		if (chdir(home) != 0)
		{
			printf("cd : Error changing directory\n");
			return (1);
		}
	}
	else
	{
		if (chdir(cmd.args[1]) != 0)
		{
			printf("cd : Error changing directory\n");
			return (1);
		}
	}
	return (0);
}

int	exec_pwd(t_list *env)
{
	char *buff;

	buff = NULL;
	(void)env;
	buff = getcwd(buff, 90000); // ghanbdloha
	printf("%s\n", buff);
	return (0);
}

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
