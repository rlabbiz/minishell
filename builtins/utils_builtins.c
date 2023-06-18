/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:25:14 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/18 21:31:59 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_list *lst, char *name) // name return value
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

void	add_var_to_env(t_list **lst, char *old_str)
{
	char	*str;
	t_env	*env;

	str = check_cmd(old_str);
	env = get_line_of_env(lst, str);
	if (env)
		ft_lstadd_back(lst, ft_lstnew(env));
	// printf("*%s*\n", str);
	free(str);
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

void	free_env(void *ptr)
{
	t_env	*env;

	env = ptr;
	free(env->name);
	free(env->value);
	free(env);
}
