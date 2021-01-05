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
				plr->x = x + 0.5;
				plr->y = y + 0.5;
				plr->dir_x = 0;
				plr->dir_y = -1;
				plr->plane_x = -0.66;
				plr->plane_y = 0;
				return;
			}
			else if (map[y][x] == 'S')
			{
				plr->x = x + 0.5;
				plr->y = y + 0.5;
				plr->dir_x = 0;
				plr->dir_y = 1;
				plr->plane_x = 0.66;
				plr->plane_y = 0;
				return;
			}
			else if (map[y][x] == 'W')
			{
				plr->x = x + 0.5;
				plr->y = y + 0.5;
				plr->dir_x = -1;
				plr->dir_y = 0;
				plr->plane_x = 0;
				plr->plane_y = 0.66;
				return;
			}
			else if (map[y][x] == 'E')
			{
				plr->x = x + 0.5;
				plr->y = y + 0.5;
				plr->dir_x = 1;
				plr->dir_y = 0;
				plr->plane_x = 0;
				plr->plane_y = -0.66;
				return;
			}
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_vert_line(t_mlx mlx, int x, int drawStart, int drawEnd, int side)
{
	int color;
	int y = 0;
	if (side == 0)
		color = 0x00FF0000;
	else
		color = 0x0000FF00;
	while (y < 480)
	{
		if (y < drawStart)
			my_mlx_pixel_put(&mlx, x, y, 0x00000000);
		else if (y > drawStart && y < drawEnd)
			my_mlx_pixel_put(&mlx, x, y, color);
		else if (y > drawEnd)
			my_mlx_pixel_put(&mlx, x, y, 0x000000FF);
		y++;
	}
}

void ft_make_image(t_mlx mlx, char **map, int width, int high)
{
	int i;
	int w;
	double cameraX;
	double rayDirX;
	double rayDirY;
// длина луча от текущей позиции до следующей стороны x или y
	double sideDistX;
	double sideDistY;
//	в какой ячеки карты?
	int x = (int)mlx.plr->x;
	int y = (int)mlx.plr->y;
	int hit = 0; // есть ли там была стена?
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int side;
	w = width;
	i = 0;
	while (i < w)
	{
		hit = 0;
		x = (int)mlx.plr->x;
		y = (int)mlx.plr->y;
//		положение луча и направление
		cameraX = 2.0 * i / w - 1.0;
		rayDirX = mlx.plr->dir_x + mlx.plr->plane_x * cameraX;
		rayDirY = mlx.plr->dir_y + mlx.plr->plane_y * cameraX;
// длина луча от одной стороны x или y до следующей стороны x или y
//		deltaDistX = sqrt (1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
//		deltaDistY = sqrt (1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		deltaDistX = abs((int)(1 / rayDirX));
		deltaDistY = abs((int)(1 / rayDirY));
// в каком направлении шагать по оси x или y (+1 или -1)
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (mlx.plr->x - x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (x + 1.0 - mlx.plr->x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (mlx.plr->y - y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mlx.plr->y + 1.0 - y) * deltaDistY;
		}
// выполняем DDA
		while (hit == 0)
		{
// переход к следующему квадрату карты, ИЛИ по оси x, ИЛИ по оси y
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				x = x + stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				y = y + stepY;
				side = 1;
			}
// Проверяем, попал ли луч в стену
			if(map[y][x] >= 1)
				hit = 1;
		}
//Вычислить расстояние, проецируемое по направлению камеры (евклидово расстояние даст эффект рыбьего глаза!)
		if(side == 0)
			perpWallDist = (x - mlx.plr->x + ((double)(1.0 - stepX) / 2)) /
					rayDirX;
		else
			perpWallDist = (y - mlx.plr->y + ((double)(1.0 - stepY) / 2)) /
			rayDirY;
// Рассчитываем высоту линии для рисования на экране
		int lineHeight = (int)(high / perpWallDist);
		if (i % 10 == 0)
			printf("|%d |  i=%d | perpWallDist=%f\n", lineHeight, i, perpWallDist);
// вычисляем самый низкий и самый высокий пиксели для заполнения текущей полосы
		int drawStart = -lineHeight / 2 + high / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + high /  2;
		if(drawEnd >= high)
			drawEnd = high;
		draw_vert_line(mlx, i, drawStart, drawEnd, side);
		i++;
	}
}

void make_cub(t_all *all)
{
	t_mlx mlx;
	t_plr plr;

	all->mlx = &mlx;
	all->file->resol_x = 640;
	all->file->resol_y = 480;
	all->mlx->plr = &plr;
	all->mlx->map = all->file->map;
	where_is_player(all->mlx->plr, all->mlx->map);
	all->mlx->mlx= mlx_init();
	all->mlx->win = mlx_new_window(all->mlx->mlx, 640, 480, "Cub3D");
	all->mlx->img = mlx_new_image(all->mlx->mlx, 640, 480);
	all->mlx->addr = mlx_get_data_addr(all->mlx->img, &all->mlx->bits_per_pixel,
									&all->mlx->line_length,	&all->mlx->endian);
	ft_make_image(*all->mlx, all->mlx->map, all->file->resol_x,
			   all->file->resol_y);
	mlx_put_image_to_window(all->mlx->mlx, all->mlx->win, all->mlx->img, 0, 0);
	mlx_hook();
	mlx_loop(all->mlx->mlx);


}
