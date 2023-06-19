/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/19 15:53:44 by rlabbiz          ###   ########.fr       */
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
	if (!path)
		return (NULL);
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
	if (node->inred != 0)
		dup2(node->inred, STDOUT_FILENO);
	if (node->outred != 0)
		dup2(node->outred, STDIN_FILENO);
}

int is_not_fork(t_cmd *cmd, t_list **lst_env)
{
	if (!ft_strncmp(cmd->args[0], "cd", 2) && ft_strlen(cmd->args[0]) == 2)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "export", 6) && ft_strlen(cmd->args[0]) == 6)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "env", 3) && ft_strlen(cmd->args[0]) == 3)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "unset", 5) && ft_strlen(cmd->args[0]) == 5)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	else if (!ft_strncmp(cmd->args[0], "exit", 4) && ft_strlen(cmd->args[0]) == 4)
	{
		builtins(cmd, lst_env);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd, t_list **lst_env, char **env)
{
	int		i;
	char	*check;
	pid_t	child_ps;
	
	i = 0;
	expand(&cmd, *lst_env);
	// printf("%s\n", cmd->args[1]);
	if (!cmd->args || !cmd->args[0])
		return ;
	// child_ps = malloc(sizeof(int ) * cmd->cmd_len);
	// if (access(s, F_OK) == 0)
	// {
	// 	if (access(s, X_OK) == 0)
	// 		return (s);
	// 	else
	// 	{
	// 		printf("bash: %s: Permission denied\n", s);
	// 		return (NULL);
	// 	}
	// }
	
	if (is_not_fork(cmd, lst_env))
		return ;
	else
	{
		check = path_cmd(cmd->args[0], *lst_env);
		if (check)
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
					execve(check, cmd->args, env);
					exit (1); //is execve failed
				}
				else
				{
					waitpid(child_ps, &status, 0);
					status = status >> 8;
				}
				i++;
			}
			
		}
		else
		{
			printf("minishell: %s: command not found\n", cmd->args[0]);
			status = 127;
		}
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
	pid = malloc(sizeof(int) * len);
	while (i < len)
	{
		check = path_cmd(cmd[i].args[0], *lst_env);
		t_cmd *env = &cmd[i]; 
		expand(&env, *lst_env);
		if (check)
		{
			pipe(pipefd);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				dup2(tmp, 0);
				if (i < len - 1)
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
				{
					execve(check, cmd[i].args, NULL);
					perror(0);
					exit(1);
				}
			}
			else
			{
				if (tmp != 0)
					close(tmp);
				if (i == len - 1)
					close(pipefd[0]);
				tmp = pipefd[0];
				close(pipefd[1]);
			}
		}
		else
			printf("minishell: command not found: %s\n", cmd[i].args[0]);
		i++;
	}
	i = -1;
	while (++i < len)
		waitpid(pid[i], &global.status, 0);
	global.status = global.status >> 8;
	free(pid);
}

void exec(t_cmd *cmd, t_list **lst_env, char **env)
{
	int	len;

	if (!cmd || !lst_env)
		return ;
	len = cmd[0].cmd_len;

	if (len == 1)
	{
		exec_cmd(&cmd[0], lst_env, env);
	}
	else if (len > 1)
	{
		pipeline(cmd, lst_env);
	}
	// free(cmd);
	// ft_lstclear(lst_env, del_env);
}
