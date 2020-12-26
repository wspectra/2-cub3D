/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:20:23 by wspectra          #+#    #+#             */
/*   Updated: 2020/12/26 21:20:25 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void where_is_player(t_plr *plr, char **map)
{
	int x;
	int y;
	plr->plane_x = 0;
	plr->plane_y = 0.66;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'W' &&
			   map[y][x] != 'E' && map[y][x] != '\0')
		{
			x++;
			if (map[y][x] == 'N')
			{
				plr->x = x;
				plr->y = y;
				plr->dir_x = 0;
				plr->dir_y = -1;
				return;
			}
			else if (map[y][x] == 'S')
			{
				plr->x = x;
				plr->y = y;
				plr->dir_x = 0;
				plr->dir_y = 1;
				return;
			}
			else if (map[y][x] == 'W')
			{
				plr->x = x;
				plr->y = y;
				plr->dir_x = -1;
				plr->dir_y = 0;
				return;
			}
			else if (map[y][x] == 'E')
			{
				plr->x = x;
				plr->y = y;
				plr->dir_x = 1;
				plr->dir_y = 0;
				return;
			}
		}
		y++;
	}
}

void ft_make_image(t_mlx mlx,char **map)
{
	int i;
	double w;

	while (mlx.addr)
	{
		i = 0;
		while (i < w)
		{

			i++;
		}
	}
}

void make_cub(t_all *all)
{
	t_mlx mlx;
	t_plr plr;

	all->mlx = &mlx;
	all->mlx->plr = &plr;
	all->mlx->map = all->file->map;
	where_is_player(all->mlx->plr, all->mlx->map);
	all->mlx->mlx= mlx_init();
	all->mlx->win = mlx_new_window(all->mlx->mlx, 640, 480, "Cub3D");
	all->mlx->img = mlx_new_image(all->mlx->mlx, 1000, 500);
	all->mlx->addr = mlx_get_data_addr(all->mlx->img, &all->mlx->bits_per_pixel,
									&all->mlx->line_length,	&all->mlx->endian);
	ft_make_image(*all->mlx, all->mlx->map);
	mlx_loop(all->mlx->mlx);


}
