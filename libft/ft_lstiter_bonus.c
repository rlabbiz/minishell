/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:55:17 by rlabbiz           #+#    #+#             */
/*   Updated: 2022/10/23 15:18:34 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void _f(void *con){
	int i = 0;
	while (*((char *)con + i) != '\0'){
		*((char *)con + i) = 'j';
		i++;
	}
}

int main(){

	t_list *a, *b;

	a = ft_lstnew(ft_strdup("reda"));
	b = ft_lstnew(ft_strdup("ali"));

	a->next = b;
	b->next = NULL;
	ft_lstiter(a, _f);

	while (a != NULL){
		printf("%s\n", a->content);
		a = a->next;
	}
	
}