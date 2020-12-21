/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <wspectra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:38:08 by wspectra          #+#    #+#             */
/*   Updated: 2020/11/09 17:49:26 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *stack, const char *ndle, size_t len)
{
	size_t	i;
	size_t	k;

	if (ndle[0] == 0)
		return ((char*)stack);
	i = 0;
	while (stack[i] != '\0' && i < len)
	{
		k = 0;
		while ((i + k) < len && ndle[k] == stack[i + k])
		{
			k++;
			if (ndle[k] == '\0')
				return ((char*)stack + i);
		}
		i++;
	}
	return (NULL);
}
