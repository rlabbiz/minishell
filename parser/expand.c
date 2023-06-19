/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:24:00 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/19 16:17:22 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char *expantion(char *str, t_list *lst_env, int check)
{
	t_list	*node = write_expantion_on_lst(lst_env, str);
	t_list	*lst = node;
	char	*arg = NULL;
	char	*cmd = NULL;
	while (lst)
	{
		arg = ft_strjoin(arg, lst->content);
		lst = lst->next;
	}
	ft_lstclear(&node, ft_del);
	if (check)
	{
		cmd = check_cmd(arg);
		free(arg);
		return (cmd);	
	}
	return (arg);
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
	while (i < len)
	{
		arr[i] = ft_strdup(node->content);
		i++;
		node = node->next;
	}
	arr[i] = NULL;
	return (arr);
}

void expand(t_cmd **list, t_list *lst_env)
{

	char c;
	t_list *command = NULL;
	command = join_arr_to_lst((*list)->args);
	if (!command)
		return ;
	t_list *node = NULL;
	node = command;
	c = 1;
	while (node != NULL)
	{
		node->content = expantion(node->content, lst_env, 1);
		node = node->next;
	}
	// ft_free_split(cmd->args);
	(*list)->args = join_lst_to_arr(command);
}
