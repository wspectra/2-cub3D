/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:59:26 by wspectra          #+#    #+#             */
/*   Updated: 2021/01/11 17:59:28 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

//void where_is_player(t_plr *plr, char **map)
//{
//	int x;
//	int y;
//
//	y = 0;
//	while (map[y] != NULL)
//	{
//		x = 0;
//		while (map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'W' &&
//			   map[y][x] != 'E' && map[y][x] != '\0')
//		{
//			x++;
//			if (map[y][x] == 'N')
//			{
//				plr->x = x + 0.5;
//				plr->y = y + 0.5;
//				plr->dir_x = 0;
//				plr->dir_y = -1;
//				plr->plane_x = -0.66;
//				plr->plane_y = 0;
//				return;
//			}
//			else if (map[y][x] == 'S')
//			{
//				plr->x = x + 0.5;
//				plr->y = y + 0.5;
//				plr->dir_x = 0;
//				plr->dir_y = 1;
//				plr->plane_x = 0.66;
//				plr->plane_y = 0;
//				return;
//			}
//			else if (map[y][x] == 'W')
//			{
//				plr->x = x + 0.5;
//				plr->y = y + 0.5;
//				plr->dir_x = -1;
//				plr->dir_y = 0;
//				plr->plane_x = 0;
//				plr->plane_y = 0.66;
//				return;
//			}
//			else if (map[y][x] == 'E')
//			{
//				plr->x = x + 0.5;
//				plr->y = y + 0.5;
//				plr->dir_x = 1;
//				plr->dir_y = 0;
//				plr->plane_x = 0;
//				plr->plane_y = -0.66;
//				return;
//			}
//		}
//		y++;
//	}
//}


void make_game(t_all *all)
{
	t_mlx mlx;
	t_plr plr;
	int size_x;
	int size_y;

	all->mlx = &mlx;
	all->mlx->plr = &plr;
	all->mlx->map = all->file->map;
//	where_is_player(all->mlx->plr, all->file->map);
	all->mlx->mlx= mlx_init();
	mlx_get_screen_size(all->mlx->mlx, &size_x, &size_y);
	if (all->file->resol_x < size_x || all->file->resol_y < size_y)
	{
		size_x = all->file->resol_x;
		size_y = all->file->resol_y;
	}
	all->mlx->win = mlx_new_window(all->mlx->mlx, size_x, size_y, "Cub3D");
	all->mlx->img = mlx_new_image(all->mlx->mlx, size_x, size_y);
	all->mlx->addr = mlx_get_data_addr(all->mlx->img, &all->mlx->bits_per_pixel,
									&all->mlx->line_length,	&all->mlx->endian);
	ft_make_image(all, all->mlx->map, size_x, size_y);
	mlx_put_image_to_window(all->mlx->mlx, all->mlx->win, all->mlx->img, 0, 0);
	mlx_loop(all->mlx->mlx);
}