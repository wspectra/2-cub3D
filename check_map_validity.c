/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:53:01 by wspectra          #+#    #+#             */
/*   Updated: 2021/01/08 16:53:03 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **make_map(char **file, int start, int end)
{
	char **map;
	int i;

	if (!(map = (char **)malloc(sizeof(char *) * (end - start + 1))))
		return (NULL);
	i = 0;
	while (file[start] != NULL)
	{
		map[i] = ft_strdup(file[start]);
		i++;
		start++;
	}
	map[i] = NULL;
	return (map);
}


void check_map_validity(t_all *all, int *start_map, int size_file, char **file)
{
	char **map;
	int start;
	int x;
	int y;
	int plr;
	start = *start_map;
	if (all->file->error == 1)
		return;
	if (!(map = make_map(file, start, size_file)))
	{
		all->file->error = 1;
		return;
	}
	y = 0;
	plr = 0;

	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0' || map[y][x] == '2')
			{
				if (check_cell(map, x, y) != 0)
				{
					printf("\nboom\n");
					all->file->error = 1;
					return;
				}
			}
			else if (map[y][x] == 'N' || map[y][x] == 'W' ||
					map[y][x] == 'E' || map[y][x] == 'S')
			{
				if (plr == 1)
				{
					all->file->error = 1;
					return;
				}
				else
					plr = 1;
			}
			else if (map[y][x] != '1' && map[y][x] != ' ')
			{
				all->file->error = 1;
				return;
			}
			x++;
		}
		y++;
	}
	if (plr == 0)
	{
		all->file->error = 1;
		return;
	}
	*start_map = size_file - 1;
}
