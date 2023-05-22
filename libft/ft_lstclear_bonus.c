/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:28 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/20 18:48:36 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(char *))
{
	t_list	*node;

	if (lst && del)
	{
		node = *lst;
		while (node != NULL)
		{
			del(node->content);
			*lst = node;
			node = node->next;
			free(*lst);
		}
		*lst = NULL;
	}
}
