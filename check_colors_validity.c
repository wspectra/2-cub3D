/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:13:38 by wspectra          #+#    #+#             */
/*   Updated: 2021/01/05 16:13:40 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static int	get_color_value(char *str, int *i)
{
	int	k;
	int	value;

	k = *i;
	if (str[k] == ',')
		k++;
	while (str[k] == ' ')
		k++;
	value = ft_isdigit(str[k]) == 1 ? 0 : -1;
	while (ft_isdigit(str[k]) == 1)
	{
		value = value * 10 + str[k] - 48;
		k++;
	}
	while (str[k] == ' ')
		k++;
	if (value > 255)
		value = -1;
	*i = k;
	return (value);
}

void		check_colors_validity(t_file *file, char *str, int i, char c)
{
	int	r;
	int	g;
	int	b;

	if (file->error == 1 || (c == 'F' && file->floor != -1) ||
		(c == 'C' && file->ceilling != -1) || str[++i] != ' ')
	{
		file->error = 1;
		return ;
	}
	r = get_color_value(str, &i);
	g = get_color_value(str, &i);
	b = get_color_value(str, &i);
	if (str[i] != '\0' || r == -1 || g == -1 || b == -1)
	{
		file->error = 1;
		return ;
	}
	printf("r %d, g %d, b %d\n\n", r, g, b);
	if (c == 'F')
		file->floor = create_rgb(r, g, b);
	else
		file->ceilling = create_rgb(r, g, b);
}
