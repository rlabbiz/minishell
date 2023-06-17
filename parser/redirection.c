/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:35:33 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/17 20:22:46 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redirections_in(t_cmd **lst, char *file)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_APPEND)
		cmd->first_rdr = RDR_IN;
	if (cmd->ifd != NONE)
		close(cmd->ifd);
	if (cmd->inred != NONE)
	{
		close(cmd->inred);
		cmd->inred = NONE;
	}
	if (access(file, F_OK) == -1)
		cmd->ifd = open(file, O_CREAT | O_WRONLY);
	else
		cmd->ifd = open(file, O_WRONLY);
}

int redirections_out(t_cmd **lst, char *file)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_HERDOC)
		cmd->first_rdr = RDR_OUT;
	if (cmd->ofd != NONE)
		close(cmd->ofd);
	if (cmd->outred != NONE)
	{
		close(cmd->outred);
		cmd->outred = NONE;
	}
	if (access(file, F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (1);
	}
	else if (access(file, R_OK) == -1)
	{
		printf("bash: %s: Permission denied\n", file);
		return (1);
	}
	cmd->ofd = open(file, O_RDONLY);
	return (0);
}

int redirections_append(t_cmd **lst, char *file)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_IN)
		cmd->first_rdr = RDR_APPEND;
	if (cmd->inred != NONE)
		close(cmd->inred);
	if (cmd->ifd != NONE)
	{
		close(cmd->ifd);
		cmd->ifd = NONE;
	}
	if (access(file, F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (1);
	}
	cmd->inred = open(file, O_RDWR | O_CREAT | O_APPEND);
	return (0);
}

void redirections_herdoc(t_cmd **lst)
{
	t_cmd	*cmd;

	cmd = *lst;
	if (cmd->first_rdr == NONE || cmd->first_rdr == RDR_OUT)
		cmd->first_rdr = RDR_HERDOC;
	if (cmd->outred != NONE)
		close(cmd->outred);
	if (cmd->ofd != NONE)
	{
		close(cmd->ofd);
		cmd->ofd = NONE;
	}
	cmd->outred = cmd->herdoc;
	cmd->herdoc = 0;
}

int	redirections(t_cmd *cmd, char *str, int rdr, t_list *lst_env)
{
	char *old_file = expantion(str, lst_env, 1);
	char *file;
	if (!old_file || check_onbiges(old_file))
	{
		printf("minishell: %s: ambiguous redirect\n", str);
		return(-1);
	}
	file = check_cmd(old_file);
	if (rdr == RDR_IN)
		redirections_in(&cmd, file);
	else if (rdr == RDR_OUT && redirections_out(&cmd, file))
		return (1);
	else if (rdr == RDR_APPEND && redirections_append(&cmd, file))
		return (1);
	else if (rdr == RDR_HERDOC)
		redirections_herdoc(&cmd);
	return (0);
}