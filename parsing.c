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

#include "cub3d.h"

void parsing (char **file)
{
	t_all	all;
	t_file	struct_file;

	all.file = &struct_file;
	all.file->map = file;
//	print_map(&all);
	make_cub(&all);

}