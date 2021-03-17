/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:49:44 by wspectra          #+#    #+#             */
/*   Updated: 2021/03/16 14:49:46 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void sorting(t_all *all)
{
	t_sprite tmp;
	int x;
	int cnt;

	x = 0;
	cnt = all->file->sp_num - 1;
	while (cnt > 0)
	{
		while (x < all->file->sp_num)
		{
			if (all->mlx->sprt[x].dist < all->mlx->sprt[x + 1].dist)
			{
				tmp = all->mlx->sprt[x];
				all->mlx->sprt[x] = all->mlx->sprt[x + 1];
				all->mlx->sprt[x + 1] = tmp;
			}
			x++;
		}
		cnt--;
	}
}

void sprite_new_pposition(t_all *all, int wid, int high)
{
	int i;

	i = 0;
	int j;
	int start;
	int color;
	int *dst;
	while (i < all->file->sp_num)
	{
		all->mlx->sprt[i].inv_det = 1.0 / (all->plr->plan_x *
				all->plr->vector_y - all->plr->vector_x * all->plr->plan_y);

		all->mlx->sprt[i].new_x = all->mlx->sprt[i].inv_det
				* (all->plr->vector_y * all->mlx->sprt[i].comp_x -
				all->plr->vector_x * all->mlx->sprt[i].comp_y);
		all->mlx->sprt[i].new_y = all->mlx->sprt[i].inv_det
				* (-all->plr->plan_y * all->mlx->sprt[i].comp_x +
				all->plr->plan_x *  all->mlx->sprt[i].comp_y);

		all->mlx->sprt[i].screen_x = (int)(wid / 2)
				* (1 + all->mlx->sprt[i].new_x / all->mlx->sprt[i].new_y);
		all->mlx->sprt[i].hight = abs((int)(high / (all->mlx->sprt[i].new_y)));

		all->mlx->sprt[i].draw_start_y = -all->mlx->sprt[i].hight / 2 + high / 2;
		if (all->mlx->sprt[i].draw_start_y < 0)
			all->mlx->sprt[i].draw_start_y = 0;
		all->mlx->sprt[i].draw_end_y = all->mlx->sprt[i].hight / 2 + high / 2;
		if (all->mlx->sprt[i].draw_end_y >= high)
			all->mlx->sprt[i].draw_end_y = high - 1;
		all->mlx->sprt[i].width = abs((int)(high / all->mlx->sprt[i].new_y));
		all->mlx->sprt[i].draw_start_x = -all->mlx->sprt[i].width / 2 +
				all->mlx->sprt[i].screen_x;
		if (all->mlx->sprt[i].draw_start_x < 0)
			all->mlx->sprt[i].draw_start_x = 0;
		all->mlx->sprt[i].draw_end_x = all->mlx->sprt[i].width / 2 +
				all->mlx->sprt[i].screen_x;
		if (all->mlx->sprt[i].draw_end_x >= wid)
			all->mlx->sprt[i].draw_end_x = wid - 1;

		start = all->mlx->sprt[i].draw_start_x;
		while (start < all->mlx->sprt[i].draw_end_x)
		{
			all->mlx->sprt[i].tex_x = (int)(256 * (start -
					(-all->mlx->sprt[i].width / 2 + all->mlx->sprt[i].screen_x)) *
					all->mlx->sprite->img_width / all->mlx->sprt[i].width) / 256;
			if (all->mlx->sprt[i].new_y > 0 && start > 0 &&
			start < wid && all->mlx->sprt[i].new_y <
			all->plr->wall_dist_array[start])
			{
				j = all->mlx->sprt[i].draw_start_y;
				while (j < all->mlx->sprt[i].draw_end_y)
				{
					all->mlx->sprt[i].d = j * 256
								 - high * 128 + all->mlx->sprt[i].hight * 128;
					all->mlx->sprt[i].tex_y = ((all->mlx->sprt[i].d *
							all->mlx->sprite->img_height)
									  / all->mlx->sprt[i].hight) / 256;
					dst = (void *)all->mlx->sprite->addr + (all->mlx->sprt[i].tex_y *
							all->mlx->sprite->line_length + all->mlx->sprt[i].tex_x *
							(all->mlx->sprite->bits_per_pixel / 8));
					color = *(int*)dst;
					if ((color & 0x00ffffff) != 0)
						my_mlx_pixel_put(all->mlx, start, j, color);
					j++;
				}
			}
			start++;
		}


		i++;
	}
}
void sprite_dist(t_all *all)
{
	int i;

	i = 0;
	while (i < all->file->sp_num)
	{
		all->mlx->sprt[i].dist = (all->plr->posX - all->mlx->sprt[i].posX) *
				(all->plr->posX - all->mlx->sprt[i].posX) +
				(all->plr->posY - all->mlx->sprt[i].posY) *
						(all->plr->posY - all->mlx->sprt[i].posY);
		all->mlx->sprt[i].comp_x = all->mlx->sprt[i].posX - all->plr->posX;
		all->mlx->sprt[i].comp_y = all->mlx->sprt[i].posY - all->plr->posY;

		i++;
	}
}
void	make_sprite(t_all *all, int wid, int high)
{
	sprite_dist(all);
	sorting(all);
	if (all->mlx->sprt[all->file->sp_num - 1].posX == all->plr->posX &&
			all->mlx->sprt[all->file->sp_num - 1].posY == all->plr->posY)
		all->file->sp_num--;
	sprite_new_pposition(all, wid, high);
	int x = 0;
	while (x < all->file->sp_num)
	{
		printf("x = %f y = %f dist = %f\n", all->mlx->sprt[x].posX,
			   all->mlx->sprt[x].posY, all->mlx->sprt[x].dist);
		x++;
	}
}