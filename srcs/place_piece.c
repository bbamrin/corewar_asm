/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/04 19:57:41 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		mdist(t_filler *filler, int i, int j)
{
	int min_d;
	int d;
	int y;
	int x;

	y = 0;
	min_d = MAXINT;
	while (filler->map->dmap[y] && (y < filler->map->h))
	{
		x = 0;
		while (filler->map->dmap[y][x] && x < filler->map->w)
		{
			if (filler->map->dmap[y][x] == ENEMY_CELL
			&& ((d = abs(x - j) + abs(y - i)) <= min_d))
				min_d = d;
			x++;
		}
		y++;
	}
	return (min_d);
}

void	piece_sum(t_filler *filler, int i, int j, int *sum)
{
	if (filler->map->dmap[i][j] == EMPTY_CELL)
		filler->map->dmap[i][j] = mdist(filler, i, j);
	if (filler->map->dmap[i][j] == PLAYER_CELL)
		*sum += mdist(filler, i, j);
	if (filler->map->dmap[i][j] != PLAYER_CELL)
		*sum += filler->map->dmap[i][j];
}

int		calc_piece_sum(t_filler *filler, int x, int y)
{
	int	j;
	int	i;
	int	sum;

	sum = 0;
	i = filler->piece->y_top_left;
	while (i >= 0 && filler->map->dmap[i]
	&& i < filler->piece->y_top_left + filler->piece->th)
	{
		j = filler->piece->x_top_left;
		while (j >= 0 && filler->map->dmap[i][j]
		&& j < filler->piece->x_top_left + filler->piece->tw)
		{
			if (filler->piece->map[i][j] == '*')
				piece_sum(filler,
				y + i - filler->piece->y_top_left,
				x + j - filler->piece->x_top_left, &sum);
			j++;
		}
		i++;
	}
	return (sum);
}

int		is_fit(t_filler *filler, int x, int y, int pc)
{
	int	j;
	int	i;

	i = filler->piece->y_top_left;
	while (i >= 0 && filler->map->dmap[i]
	&& i < filler->piece->y_top_left + filler->piece->th)
	{
		j = filler->piece->x_top_left;
		while (j >= 0 && filler->map->dmap[i]
		[j] && j < filler->piece->x_top_left + filler->piece->tw)
		{
			if (filler->piece->map[i][j] == '*')
			{
				if (filler->map->dmap[y + i - filler->piece->y_top_left]
				[x + j - filler->piece->x_top_left] == ENEMY_CELL)
					return (0);
				if (filler->map->dmap[y + i - filler->piece->y_top_left]
				[x + j - filler->piece->x_top_left] == PLAYER_CELL)
					pc++;
			}
			j++;
		}
		i++;
	}
	return (pc == 1);
}

void	place_piece(t_filler *filler, int i, int j)
{
	int sum;
	int min_sum;

	min_sum = MAXINT;
	while (filler->map->dmap[i]
	&& i <= filler->map->h - filler->piece->th)
	{
		j = 0;
		while (filler->map->dmap[i][j]
		&& j <= filler->map->w - filler->piece->tw)
		{
			if (is_fit(filler, j, i, 0))
			{
				sum = calc_piece_sum(filler, j, i);
				if (sum >= 0 && sum < min_sum)
				{
					filler->x = j - filler->piece->x_top_left;
					filler->y = i - filler->piece->y_top_left;
					min_sum = sum;
				}
			}
			j++;
		}
		i++;
	}
}
