/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:22 by wspectra          #+#    #+#             */
/*   Updated: 2020/12/21 15:42:23 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file_name_validity(char *str)
{
	int i;

	i = 0;
	while (str[i] != '.' && str[i] != '\0')
		i++;
	if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u'
		&& str[i + 3] == 'b' && str[i + 4] == '\0')
		return (1);
	else
		return (0);
}

int			main(int argc, char *argv[])
{
	int fd;

	if (argc == 2)
	{
		if (check_file_name_validity(argv[1]) == 1)
		{
			fd = open(argv[1], O_RDONLY);
			if (fd < 0)
				write(1, "Error\nCouldn't read file\n", 24);
			else
				read_file(fd);
		}
		else
			write(1, "Error\nInvalid file name\n", 24);
	}
	else
		write(1, "Error\nWrong number of arguments\n", 33);
	return (0);
}
