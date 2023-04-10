/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 08:26:27 by rlabbiz           #+#    #+#             */
/*   Updated: 2022/10/22 16:47:58 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n)
	{
		if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0')
			return ((unsigned char)*str1 - (unsigned char )*str2);
		str1++;
		str2++;
		i++;
	}
	if (i == n)
		return (0);
	return (0);
}
