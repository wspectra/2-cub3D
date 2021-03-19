/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:25:59 by wspectra          #+#    #+#             */
/*   Updated: 2021/03/18 17:26:01 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void save_bmp_file(t_all *all, int wid, int hig)
{
	int fd;
	unsigned int size;
	unsigned int i;
	char *data;
	unsigned int size_h;
	int j;
	int x;
	int y;
	int HEADER = 54;
	size = hig * wid * 3;
	if (!(data = malloc(size + HEADER)))
		return ;
	i = 0;
	while (i < size + HEADER)
		data[i++] = 0;
	size_h = hig * wid * 3;
	*(unsigned short *)data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(data + 2) = (size + HEADER);
	*(unsigned int *)(data + 6) = 0u;
	*(unsigned char *)(data + 10) = HEADER;
	*(unsigned int *)(data + 14) = 40;
	*(unsigned int *)(data + 18) = wid;
	*(unsigned int *)(data + 22) = hig;
	*(unsigned short *)(data + 26) = 1;
	*(unsigned short *)(data + 28) = 24;
	*(unsigned int *)(data + 30) = 0;
	*(unsigned int *)(data + 34) = (unsigned int)size;
	*(int *)(data + 38) = 3780;
	*(int *)(data + 42) = 3780;
	*(int *)(data + 46) = 0;
	*(int *)(data + 50) = 0;
	i = HEADER;
	y = hig;
	while (y--)
	{
		x = -1;
		while (++x < wid)
		{
			j = (x * (all->mlx->bits_per_pixel / 8)) + (y * all->mlx->line_length);
			*(data + i++) = *(all->mlx->addr + j++);
			*(data + i++) = *(all->mlx->addr + j++);
			*(data + i++) = *(all->mlx->addr + j);
		}
	}
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, data, size + HEADER);
	close (fd);
}



void			make_screenshot(t_all *all)
{
//	int fd;


//	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	save_bmp_file(all, all->plr->wid, all->plr->hig);
//	close(fd);
	all->mlx->screenshot = 1;
}

