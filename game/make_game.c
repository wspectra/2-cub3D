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

void where_is_player(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (all->file->map[y] != NULL)
	{
		x = 0;
		while (all->file->map[y][x] != 'N' && all->file->map[y][x] != 'S' &&
		all->file->map[y][x] != 'W' &&
			   all->file->map[y][x] != 'E' && all->file->map[y][x] != '\0')
		{
			x++;
			if (all->file->map[y][x] == 'N')
			{
				all->plr->map_pos_x = x;
				all->plr->map_pos_y = y;
				all->plr->posX = x + 0.5;
				all->plr->posY = y + 0.5;
				all->plr->vector_x = 0;
				all->plr->vector_y = -1;
				all->plr->plan_x = -0.66;
				all->plr->plan_y = 0;
				return;
			}
			else if (all->file->map[y][x] == 'S')
			{
				all->plr->map_pos_x = x;
				all->plr->map_pos_y = y;
				all->plr->posX = x + 0.5;
				all->plr->posY = y + 0.5;
				all->plr->vector_x = 0;
				all->plr->vector_y = 1;
				all->plr->plan_x = 0.66;
				all->plr->plan_y = 0;
				return;
			}
			else if (all->file->map[y][x] == 'W')
			{
				all->plr->map_pos_x = x;
				all->plr->map_pos_y = y;
				all->plr->posX = x + 0.5;
				all->plr->posY = y + 0.5;
				all->plr->vector_x = -1;
				all->plr->vector_y = 0;
				all->plr->plan_x = 0;
				all->plr->plan_y = 0.66;
				return;
			}
			else if (all->file->map[y][x] == 'E')
			{
				all->plr->map_pos_x = x;
				all->plr->map_pos_y = y;
				all->plr->posX = x + 0.5;
				all->plr->posY = y + 0.5;
				all->plr->vector_x = 1;
				all->plr->vector_y = 0;
				all->plr->plan_x = 0;
				all->plr->plan_y = -0.66;
				return;
			}
		}
		y++;
	}
}

void init(t_all *all)
{
	all->plr->map_pos_x = 2;
	all->plr->map_pos_y = 2;
	all->plr->posX = 2.0;
	all->plr->posY = 2.0;
	all->plr->vector_x = 1.0;
	all->plr->vector_y = 0;
	all->plr->plan_x = 0;
	all->plr->plan_y = -0.66;
}

void	ft_move_up_down(t_all *all, double c)
{
	if (all->file->map[(int)(all->plr->posY + c * all->plr->vector_y * SPEED)]
		[(int)all->plr->posX] != '1')
		all->plr->posY += all->plr->vector_y * c * SPEED;
	if (all->file->map[(int)(all->plr->posY)]
		[(int)(all->plr->posX + c * all->plr->vector_x * SPEED)] != '1')
		all->plr->posX += all->plr->vector_x * c * SPEED;
}

void	ft_move_left_right(t_all *all, double c)
{
	if (all->file->map[(int)(all->plr->posY - c * all->plr->vector_x *  SPEED)]
		[(int)all->plr->posX] != '1')
		all->plr->posY -= all->plr->vector_x * c * SPEED;
	if (all->file->map[(int)(all->plr->posY)]
		[(int)(all->plr->posX + c * all->plr->vector_y * SPEED)] != '1')
		all->plr->posX += all->plr->vector_y * c * SPEED;
}

void	ft_move_rotate(t_all *all, double c)
{
	double old_x;
	double old_plane;

	old_x = all->plr->vector_x;
	all->plr->vector_x = all->plr->vector_x * cos(c * TURN)
						 - all->plr->vector_y * sin(c * TURN);
	all->plr->vector_y = old_x * sin(c * TURN) + all->plr->vector_y * cos(c *
	 		TURN);
	old_plane = all->plr->plan_x;
	all->plr->plan_x = all->plr->plan_x * cos(c * TURN) - all->plr->plan_y *
			sin(c * TURN);
	all->plr->plan_y = old_plane * sin(c * TURN) + all->plr->plan_y * cos(c *
			TURN);
}

int		ft_close(t_all *all)
{
	mlx_destroy_window(all->mlx->mlx, all->mlx->win);
	free(all->mlx->mlx);
	exit(0);
}

int		press_key(int key, void *all)
{
	if (key == 13)
		ft_move_up_down(all, 1);
	else if (key == 1)
		ft_move_up_down(all, -1);
	else if (key == 0)
		ft_move_left_right(all, -1);
	else if (key == 2)
		ft_move_left_right(all, 1);
	else if (key == 123)
		ft_move_rotate(all, 1);
	else if (key == 124)
		ft_move_rotate(all, -1);
	else if (key == 53)
		ft_close(all);
	if (ft_make_image(all) != 1)
		return (-10);
	return (1);
}

void xpm_to_image(void *mlx,t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->img_width,
								&img->img_height);
	img->addr = (void*)mlx_get_data_addr(img->img, &img->bits_per_pixel,
									   &img->line_length, &img->endian);
}

void 	make_images(t_all *all)
{
	xpm_to_image(all->mlx->mlx, all->mlx->north, all->file->north);
	xpm_to_image(all->mlx->mlx, all->mlx->west, all->file->west);
	xpm_to_image(all->mlx->mlx, all->mlx->east, all->file->east);
	xpm_to_image(all->mlx->mlx, all->mlx->south, all->file->south);
	xpm_to_image(all->mlx->mlx, all->mlx->sprite, all->file->sprite);
}

void make_game(t_all *all)
{
	t_mlx mlx;
	t_plr plr;
	t_img north;
	t_img south;
	t_img west;
	t_img east;
	t_img sprite;

	all->mlx = &mlx;
	all->plr = &plr;
	all->mlx->sprite = &sprite;
	all->mlx->west = &west;
	all->mlx->east = &east;
	all->mlx->south = &south;
	all->mlx->north = &north;
	all->mlx->map = all->file->map;
	where_is_player(all);
	all->mlx->mlx= mlx_init();
	mlx_get_screen_size(all->mlx->mlx, &all->plr->wid, &all->plr->hig);
	make_images(all);
	if (all->file->resol_x < all->plr->wid || all->file->resol_y < all->plr->hig)
	{
		all->plr->wid = all->file->resol_x;
		all->plr->hig = all->file->resol_y;
	}
	all->mlx->win = mlx_new_window(all->mlx->mlx, all->plr->wid, all->plr->hig, "Cub3D");
	all->mlx->img = mlx_new_image(all->mlx->mlx, all->plr->wid, all->plr->hig);
	all->mlx->addr = mlx_get_data_addr(all->mlx->img, &all->mlx->bits_per_pixel,
									   &all->mlx->line_length,	&all->mlx->endian);

	ft_make_image(all);
	mlx_hook(all->mlx->win, 2, 0, press_key, all);
	mlx_hook(all->mlx->win, 17, 0, ft_close, all);
	mlx_loop(all->mlx->mlx);
}