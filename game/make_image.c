/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:08:48 by wspectra          #+#    #+#             */
/*   Updated: 2021/01/30 15:08:50 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_walls(t_all *all, int width, int high, char **map)
{

}

void	draw_floor_ceil(t_all *all, int width, int high)
{
	int x;
	int y;

	x = 0;

	while (x < width)
	{
		y = 0;
		while (y < high)
		{
			if (y < (high/2))
				my_mlx_pixel_put(all->mlx, x, y, all->file->ceilling);
			if (y >= (high/2))
				my_mlx_pixel_put(all->mlx, x, y, all->file->floor);
			y++;
		}
		x++;
	}
}

void	ft_make_image(t_all *all, char **map, int width, int high)
{
	draw_floor_ceil(all, width, high);
	draw_walls(all, width, high, map);
}
