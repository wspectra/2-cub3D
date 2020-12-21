/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <wspectra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:32:33 by wspectra          #+#    #+#             */
/*   Updated: 2020/10/31 20:45:31 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

void	*ft_bzero(void *dst, size_t n)
{
	unsigned char	*ptr1;
	size_t			i;

	i = 0;
	ptr1 = (unsigned char*)dst;
	while (i < n)
	{
		ptr1[i] = 0;
		i++;
	}
	return (dst);
}
