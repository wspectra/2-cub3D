/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:37:36 by wspectra          #+#    #+#             */
/*   Updated: 2020/12/21 16:37:38 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	make_file_structure(t_all *all)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	file->resol_x = 0;
	file->resol_y = 0;
	file->north = 0x0;
	file->south = 0x0;
	file->west = 0x0;
	file->east = 0x0;
	file->sprite = 0x0;
	file->ceilling = -1;
	file->floor = -1;
	file->error = 0;
	file->map = 0x0;
	all->file = file;
}

static int	size_of_file(char **file)
{
	int i;

	i = 0;
	while (file[i] != NULL)
		i++;
	return (i);
}
int check_errors(t_file *file)
{
	if (file->error == 1 || file->resol_x == 0 || file->north == NULL ||
			!file->west || file->east  == NULL || file->south == NULL ||
			file->sprite == NULL || file->ceilling == -1 || file->map == NULL||
			file->floor == -1)
	{
		write(1, "Error\nInvalid map data\n", 23);
		return (1);
	}
	return (0);
}
void		parsing(char **file, int save)
{
	t_all	all;
	int		x;
	int		y;

	make_file_structure(&all);
	y = 0;
	x = 0;
	all.file->save = save;
	while (file[y] != NULL)
	{
		x = 0;
		while (file[y][x] == ' ')
			x++;
		if (file[y][x] == 'R')
			check_resolution_validity(all.file, file[y], x);
		else if (ft_strchr("NSWE", (int)file[y][x]))
			check_path_validity(all.file, file[y], x);
		else if (file[y][x] == 'F' || file[y][x] == 'C')
			check_colors_validity(all.file, file[y], x, file[y][x]);
		else if (file[y][x] == '1')
			check_map_validity(&all, &y, size_of_file(file), file);
		else if (file[y][x] != '\0')
		{
			all.file->error = 1;
			break ;
		}
		y++;
	}
	if (check_errors(all.file) != 1)
	{
		make_game(&all);
	}
	delete_structure_file(&all);
}
