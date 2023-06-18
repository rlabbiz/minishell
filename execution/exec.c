/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/18 21:40:02 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

*/

char	*path_cmd(char *s, t_list *lst)
{
	char	**path;
	char	*cmd;
	int		i;

	i = 0;
	path = ft_split(get_env_value(lst, "PATH"), ':');
	while (path[i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd , s);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			free(cmd);
		i++;
	}
	return (NULL);
}

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

void	setup_red(t_cmd *node)
{
	if (node->ofd != 0)
	{
		printf("in in file....\n");
		dup2(node->ofd, STDIN_FILENO);
	}
	if (node->ifd != 0)
	{
		printf("in out file....\n");
		dup2(node->ifd, STDOUT_FILENO);
	}
	if (node->outred != 0)
		dup2(node->outred, STDOUT_FILENO);
	if (node->outred != 0)
		dup2(node->outred, STDIN_FILENO);
}

void	exec_cmd(t_cmd *cmd, t_list **lst_env)
{
	int		i;
	char	*check;
	pid_t	child_ps;

	check = path_cmd(cmd->args[0], *lst_env);
	i = 0;
	if (check)
	{
		if (!ft_strncmp(cmd[i].args[0], "cd", 2))
			builtins(cmd, lst_env);
		else
		{
			child_ps = fork();
			while (cmd->args[i])
			{
				if (child_ps == 0)
				{
					setup_red(cmd);
					if (is_builtins(cmd[i].args[0]))
					{
						exit(builtins(&cmd[i], lst_env));
					}
					execve(check, cmd->args, NULL);
				}
				else
				{
					waitpid(child_ps, &status, 0);
					status = status >> 8;
				}
				// waitpid(child_ps, &status, 0);
				i++;
			}
		}
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		status = 127;
	}
}

void	pipeline(t_cmd	*cmd, t_list **lst_env)
{
	int		pipefd[2];
	int		*pid;
	char	*check;
	int		tmp = 0;
	int		i;
	int		len;

	i = 0;
	len = cmd[0].cmd_len;
	pid = malloc(len);
	while (i < len)
	{
		check = path_cmd(cmd[i].args[0], *lst_env);
		if (check)
		{
			pipe(pipefd);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				dup2(tmp, 0);
				if (i < cmd[0].cmd_len - 1)
				{
					dup2(pipefd[1], 1);
					close(pipefd[1]);
				}
				close(pipefd[0]);
				setup_red(cmd);
				if (is_builtins(cmd[i].args[0])){
					exit (builtins(&cmd[i], lst_env));
				}
				else
					execve(check, cmd[i].args, NULL);
			}
			else
			{
				if (tmp != 0)
					close(tmp);
				if (i == cmd[i].cmd_len - 1)
					close(pipefd[0]);
				tmp = pipefd[0];
				close(pipefd[1]);
				waitpid(pid[i], &status, 0);
			}
		}
		else
			printf("minishell: command not found: %s\n", cmd[i].args[0]);
		i++;
	}
	free(pid);
}

void exec(t_cmd *cmd, t_list **lst_env)
{
	int	len;

	if (!cmd || !lst_env)
		return ;
	len = cmd[0].cmd_len;
	if (len == 1)
	{
		exec_cmd(&cmd[0], lst_env);
	}
	else if (len > 1)
	{
		pipeline(cmd, lst_env);
	}
	// free(cmd);
	// ft_lstclear(lst_env, del_env);
}