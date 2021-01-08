/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:06:34 by wspectra          #+#    #+#             */
/*   Updated: 2020/12/21 16:06:36 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**write_down(t_list *begin, int size)
{
	char	**file;
	int		i;

	if (!(file = (char **)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		file[i] = ft_strdup(begin->content);
		begin = begin->next;
		i++;
	}
	file[i] = NULL;
	return (file);
}

void		read_file(int fd)
{
	char	*line;
	char	**file;
	t_list	*list_start;

	list_start = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd_back(&list_start, ft_lstnew(line));
	}
	ft_lstadd_back(&list_start, ft_lstnew(line));
	if (!(file = write_down(list_start, ft_lstsize(list_start))))
	{
		write(1, "Error\nMemory allocation fail\n", 31);
		return ;
	}
	parsing(file);
}
