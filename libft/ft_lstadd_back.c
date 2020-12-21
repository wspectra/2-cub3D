/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <wspectra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:33:29 by wspectra          #+#    #+#             */
/*   Updated: 2020/11/09 18:33:09 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lt, t_list *new)
{
	if (!lt || !new)
		return ;
	else if (!(*lt))
		*lt = new;
	else
		ft_lstlast(*lt)->next = new;
}
