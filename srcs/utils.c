/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/04 19:57:41 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	calc_size(int i, int j, t_filler *filler)
{
	if (i < filler->piece->y_top_left)
		filler->piece->y_top_left = i;
	if (j < filler->piece->x_top_left)
		filler->piece->x_top_left = j;
	if (i > filler->piece->y_bottom_right)
		filler->piece->y_bottom_right = i;
	if (j > filler->piece->x_bottom_right)
		filler->piece->x_bottom_right = j;
	filler->piece->th =
			filler->piece->y_bottom_right - filler->piece->y_top_left + 1;
	filler->piece->tw =
			filler->piece->x_bottom_right - filler->piece->x_top_left + 1;
}

void	int_tab_free(int **tab, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(tab[i]);
}

void	heat_map_free(t_filler *filler)
{
	if (filler->map && filler->map->dmap)
	{
		int_tab_free(filler->map->dmap, filler->map->h);
		free(filler->map->dmap);
		filler->map->dmap = 0;
	}
}

void	filler_free(t_filler *filler)
{
	heat_map_free(filler);
	if (filler->map)
		free(filler->map);
	if (filler->piece)
		free(filler->piece);
	free(filler);
}

int		abs(int n)
{
	return (n > 0 ? n : -1 * n);
}
