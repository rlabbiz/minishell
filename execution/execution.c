/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/17 09:23:01 by rlabbiz          ###   ########.fr       */
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

char *ft_chardup(char c)
{
	char *str;
	
	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_list	*write_expantion_on_lst(t_list *lst_env, char *str)
{
	int qoutes;
	int i;
	char *name;
	char *line;
	char *env;
	t_list *lst;
	char c;

	i = 0;
	qoutes = 0;
	name = NULL;
	env = NULL;
	lst = NULL;
	line = str;
	while (line && *line)
	{
		i = 0;
		if (*line == '$' && qoutes != SINGLE_QUOTES)
		{
			while (line[i] && line[i] == '$')
			{
				find_quotes(line, i, &qoutes);
				i++;
			}
			if (line[i] && line[i] == '"')
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_chardup('$')));
				line = line + 1;
				continue;
			}
			else if ((i > 1 || (i == 1 && !line[i + 1])) && (i % 2) != 0)
			{
				if (i == 1 && !line[i + 1])
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup("$")));
					line = line + i;
				}
				else
					line = line + i - 1;
				continue ;
			}
			else if (i == 1 && line[i + 1] && !ft_isdigit(line[i + 1]))
			{
				line++;
				if (!*line)
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup("$")));
					continue ;
				}
				while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
				{
					find_quotes(line, i, &qoutes);
					i++;
				}
				name = ft_substr(line, 0, i);
				if (name)
				{
					env = get_env_value(lst_env, name);
					free(name);
				}
				if (env)
				{
					if (qoutes == 0)
					{
						char **arr;
						int j = 0;
						arr = ft_split(env, ' ');
						if (arr)
						{
							while (arr[j])
							{
								c = 1;
								ft_lstadd_back(&lst, ft_lstnew(ft_chardup(c)));
								ft_lstadd_back(&lst, ft_lstnew(ft_strdup(arr[j])));
								ft_lstadd_back(&lst, ft_lstnew(ft_chardup(c)));
								j++;
							}
							// ft_free_arr(arr);
						}
					}
					else
					{
						c = 1;
						ft_lstadd_back(&lst, ft_lstnew(ft_chardup(c)));
						ft_lstadd_back(&lst, ft_lstnew(ft_strdup(env)));
						ft_lstadd_back(&lst, ft_lstnew(ft_chardup(c)));
					}
				}
			}
		}
		else if (*line == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				find_quotes(line, i, &qoutes);
				i++;
			}
			if (line[i] == '\'')
				i++;
			env = ft_substr(line, 0, i);
			if (env)
			{
				ft_lstadd_back(&lst, ft_lstnew(env));
			}
		}
		else
		{
			while (line[i] && line[i] != '$')
			{
				find_quotes(line, i, &qoutes);
				i++;
			}
			env = ft_substr(line, 0, i);
			if (env)
			{
				ft_lstadd_back(&lst, ft_lstnew(env));
			}
			
			if (i == 0)
			{
				c = line[i];
				ft_lstadd_back(&lst, ft_lstnew(ft_chardup(c)));
				i++;
			}
		}
		line = line + i;
	}
	return (lst);
}

char *expantion(char *str, t_list *lst_env)
{
	t_list *node = write_expantion_on_lst(lst_env, str);
	t_list *lst = node;
	char *arg = NULL;
	char *cmd = NULL;
	while (lst)
	{
		arg = ft_strjoin(arg, lst->content);
		lst = lst->next;
	}
	cmd = check_cmd(arg);
	printf("%s\n", cmd);
	// free(str);
	return (cmd);
}

t_list *join_arr_to_lst(char **args)
{
	if (!args || !*args)
		return (NULL);
	int	i;
	t_list *lst;
	
	i = 0;
	lst = NULL;
	while (args[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(args[i])));
		// free(args[i]);
		i++;
	}
	// free(args);
	return (lst);
}

char **join_lst_to_arr(t_list *lst)
{
	t_list *node = lst;
	t_list *new;
	char **tmp;
	char **arr;
	char c;
	int i;
	int len;

	i = 0;
	new = NULL;
	while (node)
	{
		c = 1;
		if (ft_strchr(node->content, c))
		{
			tmp = ft_split(node->content, c);
			i = 0;
			while (tmp[i])
			{
				ft_lstadd_back(&new, ft_lstnew(ft_strdup(tmp[i])));
				i++;
			}
		}
		else
			ft_lstadd_back(&new, ft_lstnew(ft_strdup(node->content)));
		node = node->next;
	}
	len = ft_lstsize(new);
	arr = (char **)malloc(sizeof(char *) * len + 1);
	i = 0;
	node = new;
	while (i < len && node)
	{
		arr[i] = ft_strdup(node->content);
		i++;
		node = node->next;
	}
	
	return (arr);
}

void expand(t_cmd **list, t_list *lst_env)
{
	t_cmd *cmd = *list;
	char c;
	t_list *command = NULL;
	
	command = join_arr_to_lst(cmd->args);
	if (!command)
		return ;
	t_list *node = NULL;
	node = command;
	c = 1;
	while (node != NULL)
	{
		node->content = expantion(node->content, lst_env);
		node = node->next;
	}
	cmd->args = join_lst_to_arr(command);
}

void	one_cmd(t_cmd *cmd, t_list **lst_env)
{
	if (!cmd->args || !cmd->args[0])
		return ;
	expand(&cmd, *lst_env);
	if (!cmd->args || !cmd->args[0])
		return ;
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

