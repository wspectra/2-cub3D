/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:26:14 by wspectra          #+#    #+#             */
/*   Updated: 2021/03/15 16:26:16 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"
void what_pixel(t_img *img, t_all *all, int hig,  t_pixel *pixel)
{
	if (all->plr->side == 0)
		pixel->wall = all->plr->posY
						 + all->plr->wall_dist * all->plr->ray_dir_y;
	else
		pixel->wall = all->plr->posX
						 + all->plr->wall_dist * all->plr->ray_dir_x;
	pixel->wall -= floor(pixel->wall);
	pixel->x = (int)(pixel->wall * img->img_height);///здесть
	// длинна или ширина эрана????

	if ((all->plr->side == 0 && all->plr->ray_dir_x > 0)
		|| (all->plr->side == 1 && all->plr->ray_dir_y < 0))
		pixel->x = img->img_height - pixel->x - 1;
	pixel->step = 1.0 * img->img_height / all->plr->hight_line;
	pixel->pos = (all->plr->start_line- hig / 2
					 + all->plr->hight_line / 2) * pixel->step;
}
