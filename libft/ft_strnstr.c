/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:18:09 by rlabbiz           #+#    #+#             */
/*   Updated: 2022/10/22 16:48:06 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	j = 0;
	i = 0;
	little_len = ft_strlen(little);
	if (!little_len || little == big)
		return ((char *)big);
	if (!len && !big)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		while (big[i + j] == little[j] && (j + i) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
