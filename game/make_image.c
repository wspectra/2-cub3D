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

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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



static void	ft_hit(t_all *all)
{
	while (all->plr->hit == 0)
	{
		if (all->plr->side_x < all->plr->side_y)
		{
			all->plr->side_x += all->plr->delta_x;
			all->plr->map_pos_x += all->plr->step_x;
			all->plr->side = 0;
		}
		else
		{
			all->plr->side_y += all->plr->delta_y;
			all->plr->map_pos_y += all->plr->step_y;
			all->plr->side = 1;
		}
		if ((all->file->map[(int)floor(all->plr->map_pos_y)]
		[(int)floor(all->plr->map_pos_x)]) == '1')		//! map_pos_x & y
			all->plr->hit = 1;
	}
}

static void	ft_pos_camera_x(t_all *all, int i, int wid)
{
	double	camera_x;

	camera_x = 2 * i / (double)wid - 1;
	all->plr->ray_dir_x = all->plr->vector_x + all->plr->plan_x * camera_x;
	all->plr->ray_dir_y = all->plr->vector_y + all->plr->plan_y * camera_x;
	all->plr->map_pos_x = (int)floor(all->plr->posX);
	all->plr->map_pos_y = (int)floor(all->plr->posY);
	all->plr->delta_x = fabs(1 / all->plr->ray_dir_x);
	all->plr->delta_y = fabs(1 / all->plr->ray_dir_y);
}

static void	ft_start_and_end(t_all *all, int hig)
{
	if (all->plr->side == 0)
		all->plr->wall_dist = (all->plr->map_pos_x - all->plr->posX
							   + (double)(1 - all->plr->step_x) / 2) / all->plr->ray_dir_x;
	else
		all->plr->wall_dist = (all->plr->map_pos_y - all->plr->posY
							   + (double)(1 - all->plr->step_y) / 2) / all->plr->ray_dir_y;
	all->plr->hight_line = (int)(hig / all->plr->wall_dist);
	all->plr->start_line = -all->plr->hight_line / 2 + hig / 2;
	if (all->plr->start_line < 0)
		all->plr->start_line = 0;
	all->plr->end_line = all->plr->hight_line / 2 + hig / 2;
	if (all->plr->end_line >= hig)
		all->plr->end_line = hig;
}

static void	ft_ray_dir(t_all *all)
{
	if (all->plr->ray_dir_x < 0)
	{
		all->plr->step_x = -1;
		all->plr->side_x = (all->plr->posX - all->plr->map_pos_x)
						   * all->plr->delta_x;
	}
	else
	{
		all->plr->step_x = 1;
		all->plr->side_x= (all->plr->map_pos_x + 1.0 - all->plr->posX)
						  * all->plr->delta_x;
	}
	if (all->plr->ray_dir_y < 0)
	{
		all->plr->step_y = -1;
		all->plr->side_y = (all->plr->posY - all->plr->map_pos_y)
						   * all->plr->delta_y;
	}
	else
	{
		all->plr->step_y = 1;
		all->plr->side_y = (all->plr->map_pos_y + 1.0 - all->plr->posY)
						   * all->plr->delta_y;
	}
}

t_img *what_texture(t_all *all)
{
	if (all->plr->side == 1 && all->plr->ray_dir_y > 0)
		return(all->mlx->south);
	else if (all->plr->side == 1 && all->plr->ray_dir_y < 0)
		return(all->mlx->north);
	else if (all->plr->side == 0 && all->plr->ray_dir_x > 0)
		return(all->mlx->west);
	else
		return(all->mlx->east);
}
static void			ft_sky_earth(t_all *all, int j, int hig)
{
	t_pixel 	pixel;
	int			i;
	int color;
	int *dst;
	t_img *image;

	image = what_texture(all);
	all->mlx->pixel = &pixel;
	what_pixel(image, all, hig,  &pixel);

	i = all->plr->start_line;
	while (i < all->plr->end_line)
	{
		pixel.y = (int)pixel.pos & (image->img_width - 1);
		pixel.pos += pixel.step;
		dst = (void *)image->addr + (pixel.y * image->line_length +
								   pixel.x * (image->bits_per_pixel / 8));
		color = *(int*)dst;
		my_mlx_pixel_put(all->mlx, j, i, color);
		i++;
	}
}

int			draw_walls(t_all *all, int wid, int high)
{
	if (!(all->plr->wall_dist_array = (double*)malloc(sizeof(double ) * wid)))
		return (all->file->error = -1); // ошибка малока
	int i = 0;
	while (i < wid)
	{
		all->plr->hit = 0;
		ft_pos_camera_x(all, i, wid);
		ft_ray_dir(all);
		ft_hit(all);
		ft_start_and_end(all, high);
		ft_sky_earth(all, i, high);
		all->plr->wall_dist_array[i] = all->plr->wall_dist;
		i++;
	}
	return (1);
}

int	ft_make_image(t_all *all)
{
	draw_floor_ceil(all, all->plr->wid, all->plr->hig);
	draw_walls(all, all->plr->wid, all->plr->hig);
	make_sprite(all, all->plr->wid, all->plr->hig);
//	draw_coin(all, all->plr->wid, all->plr->hig);
	free(all->plr->wall_dist_array);
	mlx_put_image_to_window(all->mlx->mlx, all->mlx->win, all->mlx->img, 0,
							0);
	if (all->mlx->screenshot == 0 && all->file->save == 1)
		make_screenshot(all);

	return (0);
}
