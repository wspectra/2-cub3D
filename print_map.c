/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:45:56 by wspectra          #+#    #+#             */
/*   Updated: 2020/12/21 16:45:57 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void put_pixels(int x, int y, int color, t_mlx *mlx)
{
	int size;
	int a;
	int b;
	size = 30;
	b = 0;
	while (b < size)
	{
		a = 0;
		while (a < size)
		{
			my_mlx_pixel_put(mlx, (x * size) + a, (y * size) + b, color);
			a++;
		}
		b++;
	}
}

void ft_make_image(t_mlx mlx,char **map)
{
	int x;
	int y;

	y = 0;
	while(map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1')
				put_pixels(x, y, 0x00FF0000, &mlx);
			if (map[y][x] == '2')
				put_pixels(x, y, 0x00FFFF00, &mlx);
			if (map[y][x] == '0' || map[y][x] == 'N')
				put_pixels(x, y, 0x00C0C0C0, &mlx);
//			if (map[y][x] == 'N')
//				put_pixels(x, y, 0x00FF007F, data);
			x++;
		}
		y++;
	}
}

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
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W' ||
				map[y][x] == 'E')
			{
				plr->x = x;
				plr->y = y;
				return;
			}
		}
		y++;
	}
}

void ft_make_pers(t_mlx *mlx, int x, int y)
{
	int size;
	int a;
	int b;
	size = 30;
	b = 0;
	while (b < size)
	{
		a = 0;
		while(a < size)
		{
			my_mlx_pixel_put(mlx, (x * size) + a, (y*size) + b, 0x000000FF);
			a++;
		}
		b++;
	}

}
int	key_hook(int keycode, t_mlx *mlx)
{
	ft_make_image(*mlx, mlx->map);
	if (keycode == 0 && mlx->map[mlx->plr->y][mlx->plr->x - 1] != '1')
	{
		mlx->plr->x = mlx->plr->x - 1;

		ft_make_pers(mlx, mlx->plr->x, mlx->plr->y);
	}
	if (keycode == 1 && mlx->map[mlx->plr->y + 1][mlx->plr->x] != '1')
	{
		mlx->plr->y = mlx->plr->y + 1;
		ft_make_pers(mlx, mlx->plr->x, mlx->plr->y);
	}
	if (keycode == 2 && mlx->map[mlx->plr->y][mlx->plr->x + 1] != '1')
	{
		mlx->plr->x = mlx->plr->x + 1;
		ft_make_pers(mlx, mlx->plr->x, mlx->plr->y);
	}
	if (keycode == 13 && mlx->map[mlx->plr->y - 1][mlx->plr->x] != '1')
	{
		mlx->plr->y = mlx->plr->y - 1;
		ft_make_pers(mlx, mlx->plr->x, mlx->plr->y);
	}
	else
		ft_make_pers(mlx, mlx->plr->x, mlx->plr->y);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
//	printf("You pushed %d\n", keycode);
//	*vars = *vars;
	return (0);
}
void print_map(t_all *all)
{
	t_mlx mlx;
	t_plr plr;

	all->mlx = &mlx;
	all->mlx->plr = &plr;
	all->mlx->map = all->file->map;
	where_is_player(all->mlx->plr, all->mlx->map);
	all->mlx->mlx= mlx_init();
	all->mlx->win = mlx_new_window(all->mlx->mlx, 1000, 500, "Cub3D");
	all->mlx->img = mlx_new_image(all->mlx->mlx, 1000, 500);
	all->mlx->addr = mlx_get_data_addr(all->mlx->img, &all->mlx->bits_per_pixel,
									&all->mlx->line_length,	&all->mlx->endian);
	ft_make_image(*all->mlx, all->mlx->map);
	ft_make_pers(all->mlx, all->mlx->plr->x, all->mlx->plr->y);
	mlx_put_image_to_window(all->mlx->mlx, all->mlx->win, all->mlx->img, 0, 0);
	mlx_hook(all->mlx->win, 2, 1L<<0, key_hook, &mlx);
	mlx_loop(all->mlx->mlx);
//	printf ("%d  %d", all->mlx->plr->x, all->mlx->plr->y);
}