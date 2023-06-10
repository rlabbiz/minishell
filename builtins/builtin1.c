/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:30:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/10 21:24:08 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int env_is_valid(t_list *lst, char *name)
{
	char	*env;

	env = get_env_value(lst, name);
	if (env)
		return (1);
	return (0);
}

t_env *get_value_of_env(t_list **lst, char *str)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	i = 0;
	if (str[i] && (ft_isdigit(str[i]) || str[i] == '='))
	{
		printf("bash: export: `%s': not a valid identifier\n", str);
		return (NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	env->name = ft_substr(str, 0, i);
	if (str[i] && str[i] == '=' && !str[i + 1])
		env->value = ft_strdup("");
	else
	{
		while (*str && *str != '=')
			str++;
		if (*str && *str == '=')
			str++;
		if (*str)
			env->value = ft_substr(str, 0, ft_strlen(str));
	}
	if (get_env_value(*lst, env->name))
	{
		// printf("here\n");
		unset_env(lst, env->name);
	}
	// printf("pleas\n");
	return (env);
}

t_list	*get_env(t_list **lst, char **str)
{
	t_list	*lst_env;
	int		i;

	i = 0;
	while (str[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(get_value_of_env(lst, str[i])));
		i++;
	}
	return (lst_env);
}

char *get_env_value(t_list *lst, char *name)
{
	t_list	*node;
	t_env	*env;

	node = lst;
	if (!name)
		return (NULL);
	while (node)
	{
		env = node->content;
		if (ft_strlen(name) == ft_strlen(env->name))
			if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
				return (env->value);
		node = node->next;
	}
	return (NULL);
}

void	export_env(t_list **lst, char *old_str)
{
	char	*str;
	t_env	*env;

	str = check_cmd(old_str);
	env = get_value_of_env(lst, str);
	if (env)
		ft_lstadd_back(lst, ft_lstnew(env));
	// printf("*%s*\n", str);
	free(str);
}

void del_env(void *ptr)
{
	t_env	*env;

	env = ptr;
	free(env->name);
	free(env->value);
	free(env);
}

void	unset_env(t_list **lst, char *name)
{
	t_list	*node;
	t_list	*prive;
	t_list	*next;
	t_env	*env;

	node = *lst;
	env = node->content;
	prive = node;
	if (name && name[0] && ft_isdigit(name[0]))
		printf("minishell: unset: `%s': not a valid identifier\n", name);
	if (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0 && ft_strlen(env->name) == ft_strlen(name))
	{
		*lst = node->next;
		ft_lstdelone(node, del_env);
		return ;
	}
	while (node)
	{
		env = node->content;
		next = node->next;
		if (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0 && ft_strlen(env->name) == ft_strlen(name))
		{
			prive->next = node->next;
			ft_lstdelone(node, del_env);
		}
		else
			prive = node;
		node = next;
	}
}

void	print_env(t_list *lst)
{
	t_list	*node;
	t_env	*env;

	node = lst;
	while (node)
	{
		env = node->content;
		printf("%s=%s\n", env->name, env->value);
		node = node->next;
	}
}
