/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:build-in/builtins.c
/*   Created: 2023/06/08 16:30:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/08 16:30:46 by ael-amin         ###   ########.fr       */
=======
/*   Created: 2023/06/05 16:42:27 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/08 12:51:21 by rlabbiz          ###   ########.fr       */
>>>>>>> 365cda3833e6e0ed1cd2a375c3a8e5e37c395dd9:build-in/build_in.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	
	str = check_cmd(old_str);
	printf("*%s*\n", str);
	ft_lstadd_back(lst, ft_lstnew(get_value_of_env(str)));
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