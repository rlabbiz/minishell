/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 08:26:27 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/17 16:44:10 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	const char	*s1;
	const char	*s2;

	s1 = str1;
	s2 = str2;
	i = 0;
	if (!n)
		return (0);
	while (i < n)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
			return ((unsigned char)*s1 - (unsigned char )*s2);
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	return (0);
}
