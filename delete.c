/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:24:52 by wspectra          #+#    #+#             */
/*   Updated: 2021/01/09 17:24:53 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_file(char **file)
{
	int i;

	i = 0;
	while (file[i] != NULL)
	{
		free(file[i]);
		file[i] = NULL;
		i++;
	}
	free(file);
	file = NULL;
}

void	delete_structure_file(t_all *all)
{
	free(all->file->north);
	all->file->north = NULL;
	free(all->file->south);
	all->file->south = NULL;
	free(all->file->west);
	all->file->west = NULL;
	free(all->file->east);
	all->file->east = NULL;
	free(all->file->sprite);
	all->file->sprite = NULL;
	if (all->file->map)
		delete_file(all->file->map);
	free(all->file);
	all->file = NULL;
}
