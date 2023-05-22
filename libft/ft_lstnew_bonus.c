/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:31:11 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/05/20 18:47:26 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new_mode;

	new_mode = malloc(sizeof(t_list));
	if (!new_mode)
		return (NULL);
	new_mode->content = content;
	new_mode->next = NULL;
	return (new_mode);
}
