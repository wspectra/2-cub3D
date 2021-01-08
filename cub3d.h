/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:14 by wspectra          #+#    #+#             */
/*   Updated: 2020/12/21 15:42:16 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "./libft/libft.h"
# include "./mlx/mlx.h"

typedef struct	s_plr
{
	int			x;
	int			y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_plr;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
	t_plr	*plr;
}				t_mlx;

typedef struct	s_file
{
	int		resol_x;
	int		resol_y;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		ceilling;
	int		floor;
	int		error;
	char	**map;
}				t_file;

typedef struct	s_all
{
	t_file	*file;
	t_mlx	*mlx;
}				t_all;

void			read_file(int fd);
void			parsing (char **file);
void			print_map(t_all *all);
void			make_cub(t_all *all);
void			check_colors_validity(t_file *file, char *str, int i, char c);
void			check_resolution_validity(t_file *file, char *str, int i);
void			check_path_validity(t_file *file, char *str, int i);
void			check_map_validity(t_all *all, int *start_map,
						int size_file, char **file);
int check_cell(char **map, int x, int y);

#endif
