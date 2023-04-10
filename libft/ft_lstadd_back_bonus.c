/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:25:12 by rlabbiz           #+#    #+#             */
/*   Updated: 2022/10/22 16:44:25 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = *lst;
	if (!lst && !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->next = new;
	new->next = NULL;
}
