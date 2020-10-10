/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/04 19:57:41 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

t_filler	*init_filler(void)
{
	t_filler	*ret;

	if ((ret = (t_filler *)ft_memalloc(sizeof(t_filler))))
	{
		ret->player = 0;
		ret->enemy = 0;
		ret->x = 0;
		ret->y = 0;
		if (!(ret->map = (t_map *)ft_memalloc(sizeof(t_map))))
		{
			free(ret);
			return (0);
		}
		if (!(ret->piece = (t_piece *)ft_memalloc(sizeof(t_piece))))
		{
			free(ret->map);
			free(ret);
			return (0);
		}
		ret->map->dmap = 0;
		ret->piece->height = 0;
		return (ret);
	}
	return (0);
}
