/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <wspectra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:12:13 by wspectra          #+#    #+#             */
/*   Updated: 2020/11/05 20:21:32 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sizeint(int n)
{
	int size;

	if (n < 0)
	{
		size = 1;
		n = n * (-1);
	}
	else
		size = 0;
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
	else
	{
		if (!(str = (char*)malloc(sizeof(char) * (ft_sizeint(n) + 1))))
			return (NULL);
		i = ft_sizeint(n) - 1;
		str[ft_sizeint(n)] = '\0';
		if (n < 0)
		{
			str[0] = '-';
			n = n * (-1);
		}
		while (n > 9)
		{
			str[i] = n % 10 + 48;
			n = n / 10;
			i--;
		}
		str[i] = n + 48;
		return (str);
	}
}
