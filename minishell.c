/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/05 17:40:27 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del(void *data)
{
	free(data);
}

int ft_check_command(char *path, char *line)
{
	char *command;

	command = ft_strjoin(path, line);
	if (access(command, F_OK) == 0)
	{
		free(command);
		return (1);
	}
	free(command);
	return (0);
}

void print(t_cmd *cmd)
{
	int i = 0;
	int j = 0;
	int len = cmd[0].cmd_len;
	while (i < len)
	{
		printf("--------	command %d	---------\n", i + 1);
		printf("-	args:\t\t\t\t-\n");
		j = 0;
		while (cmd[i].args[j] != NULL)
		{
			printf("--  		%s\t\t\t-\n", cmd[i].args[j]);
			j++;
		}
		printf("-	ifd: %d\t\t\t\t-\n", cmd[i].ifd);
		printf("-	ofd: %d\t\t\t\t-\n", cmd[i].ofd);
		printf("-	inred: %d\t\t\t-\n", cmd[i].inred);
		printf("-	outred: %d\t\t\t-\n", cmd[i].outred);
		printf("-	herdoc: %d\t\t\t-\n", cmd[i].herdoc);
		printf("-	first_rdr: %d\t\t\t-\n", cmd[i].first_rdr);
		printf("-	cmd_len: %d\t\t\t-\n", cmd[i].cmd_len);
		printf("-----------------------------------------\n");
		i++;
	}
}

char *get_line(void)
{
	char *prompt;;
	char *line;
	prompt = ft_strdup("minishell$ ");
	line = readline(prompt);
	while (line[0] == '\0')
	{
		free(line);
		line = readline(prompt);
	}
	free(prompt);
	return (line);
}

t_env *get_value_of_env(char *str)
{
	t_env	*env;
	int		i;
	
	env = malloc(sizeof(t_env));
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	env->name = ft_substr(str, 0, i);
	while (*str && *str != '=')
		str++;
	if (*str && *str == '=')
		str++;
	if (*str)
		env->value = ft_substr(str, 0, ft_strlen(str));
	return (env);
}

t_list	*get_env(char **str)
{
	t_list	*lst_env;
	int		i;
	
	i = 0;
	while (str[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(get_value_of_env(str[i])));
		i++;
	}
	return (lst_env);	
}

void	export_env(t_list **lst, char *old_str)
{
	char	*str;
	
	str = check_cmd(old_str);
	printf("*%s*\n", str);
	ft_lstadd_back(lst, ft_lstnew(get_value_of_env(str)));
	free(str);
}

void	unset_env(t_list **lst, char *name)
{
	t_list	*node;
	t_list	*prive;
	t_env	*env;

	node = *list;
	env = NULL;
	prive = node;
	while (node)
	{
		env = node->content;
		if (ft_strncmp(env->name, name, ft_strlen(env->name)), && ft_strlen(env->name) == ft_strle(name))
		{
			prive->next = node->next;
			ft_lstdelone();
		}
		prive = node;
		node = node->next;
	}
}


void	print_env(t_list *lst)
{
	t_list	*node;
	t_env	*env;
	
	node = lst;
	env = NULL;
	while (lst)
	{
		env = lst->content;
		printf("%s=%s\n", env->name, env->value);
		lst = lst->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char *line;
	t_list *list;
	t_cmd *cmd;
	t_list *lst_env;
	(void)ac;
	(void)av;
	
	lst_env = get_env(env);
	// print_env(lst_env);
	line = get_line();
	while (line != NULL)
	{ 
		list = NULL;
		add_history(line);
		split_cmd(line, &list);
		free(line);
		if (!check_node(list))
		{
			cmd = parser(list);
			if (cmd)
				print(cmd);
		}
		line = get_line();
	}
	return (0);
}
