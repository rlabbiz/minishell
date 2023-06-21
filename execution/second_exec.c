/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:53:54 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/21 18:06:32 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_last_status(int stts)
{
	status = stts;
}

int	get_last_status(void)
{
	return (status);
}

int	get_exit_status(int pid)
{
	int		stts;
	char	*ptr;

	if (pid <= 0)
		return (get_last_status());
	waitpid(pid, &stts, 0);
	ptr = (char *) &stts;
	if (*ptr)
		return (*ptr + 128);
	return (*(ptr + 1));
}

static char	*path_cmd_(char *s, t_list *lst)
{
	char	**path;
	char	*cmd;
	int		i;

	if (access(s, F_OK) == 0)
		return (ft_strdup(s));
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

static void	setup_red_(t_cmd *node)
{
	if (node->ofd != 0)
	{
		dup2(node->ofd, STDIN_FILENO);
		close(node->ofd);
	}
	if (node->ifd != 0)
	{
		dup2(node->ifd, STDOUT_FILENO);
		close(node->ifd);
	}
	if (node->inred != 0)
	{
		dup2(node->inred, STDOUT_FILENO);
		close(node->inred);
	}
	if (node->outred != 0)
	{
		dup2(node->outred, STDIN_FILENO);
		close(node->outred);
	}
}

void	handle_pipes(int *pipes, int fd)
{
	close(fd);
	if (pipes == NULL)
		return ;
	if (pipes[0] != -1)
		dup2(pipes[0], 0);
	if (pipes[1] != -1)
		dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
}

int	exec_builtin(t_cmd *cmd, t_list **env)
{
	int	ret;
	int	fds[2];

	if (cmd->outred)
	{
		set_last_status(1);
		return (1);
	}
	fds[0] = dup(0);
	fds[1] = dup(1);
	setup_red_(cmd);
	ret = builtins(cmd, env);
	dup2(fds[0], 0);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	set_last_status(ret);
	return (-1);
}

int	exec_one_cmd(t_cmd *cmd, int *pipes, int fd, int must_fork, t_list **env, char **e)
{
	char	*path;
	int		pid;
	int		i;

	i = 0;
	if (is_builtins(cmd[i].args[0]) && must_fork == 0)
		return (exec_builtin(&cmd[i], env));
	pid = fork();
	if (pid)
		return (pid);
	if (cmd->outred)
		exit (1);
	handle_pipes(pipes, fd);
	setup_red_(cmd);
	if(is_builtins(cmd[i].args[0]))
		exit(builtins(cmd, env));
	path = path_cmd_(cmd[i].args[0], *env);
	// env_arr = env_list_to_arry(env);
	execve(path, cmd[i].args, e);
	perror("minishell");
	return (exit(1), 1);
}

int	exec_multiple_cmds(t_cmd *cmd, t_list **env, char **e, int	cmd_count)
{
	int	fds[2];
	int	p[3];
	int	fd;
	int	i;
	int pid;

	i = -1;
	while (++i < cmd_count)
	{
		if (i != cmd_count - 1)
			pipe(fds);
		if (i == 0)
		{
			p[0] = -1;
			p[1] = fds[1];
			fd = fds[0];
		}
		else if (i == cmd_count -1)
		{
			p[0] = fd;
			p[1] = -1;
			fd = -1;
		}
		else
		{
			p[0] = fd;
			p[1] = fds[1];
			fd = fds[0];
		}
		pid = exec_one_cmd(&cmd[i], p, fd, 1, env, e);
		close(p[0]);
		close(p[1]);
	}
	return(pid);
}

void	execute(t_cmd *cmd, t_list **env, char **e)
{
	int	pid;
	int	cmd_count;
	int	stts;

	pid = 0;
	cmd_count = cmd[0].cmd_len;
	if (cmd_count == 1)
	{
		pid = exec_one_cmd(cmd, NULL, -1, 0, env, e);
		if (pid > 0)
		{
			stts = get_exit_status(pid);
			set_last_status(stts);
		}
		return ;
	}
	else
	{
		pid = exec_multiple_cmds(cmd, env, e, cmd_count);
		set_last_status(get_exit_status(pid));
		while (waitpid(-1, &stts, 0) != -1)
			;
	}
}
