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

int		get_heat_map_cell(t_filler *filler, char c)
{
	if (c == '.')
		return (EMPTY_CELL);
	if (ft_tolower(c) == filler->player)
		return (PLAYER_CELL);
	if (ft_tolower(c) == filler->enemy)
		return (ENEMY_CELL);
	return (ERROR_CODE);
}

int		set_size(t_filler *filler, int mode, char **str)
{
	int	i;

	i = 0;
	if (get_next_line(MODE, str) <= 0)
		return (0);
	while ((*str)[i] && !((*str)[i] >= '0' && (*str)[i] <= '9'))
		++i;
	if ((*str)[i] == 0)
		return (0);
	if (mode)
		filler->map->h = ft_atoi(&((*str)[i]));
	else
		filler->piece->height = ft_atoi(&((*str)[i]));
	while ((*str)[i] && ((*str)[i] >= '0' && (*str)[i] <= '9'))
		++i;
	if ((*str)[i] == 0)
		return (0);
	if (mode)
		filler->map->w = ft_atoi(&((*str)[i]));
	else
		filler->piece->width = ft_atoi(&((*str)[i]));
	return (1);
}

int		set_map(t_filler *filler, char **str, int i, int j)
{
	int	k;

	if (!(filler->map->dmap =
			(int **)ft_memalloc(sizeof(int *) * (filler->map->h + 1))))
		return (0);
	while ((j = 0) == 0 && ++i < filler->map->h && get_next_line(MODE, str) > 0)
	{
		while ((*str)[j] && !((*str)[j] == 'X' || (*str)[j] == 'x'
		|| (*str)[j] == 'o' || (*str)[j] == 'O' || (*str)[j] == '.'))
			j++;
		if ((k = -1) && (*str)[j] == 0)
			return (0);
		if (!(filler->map->dmap[i] =
				(int *)ft_memalloc(sizeof(int) * (filler->map->w + 1))))
			return (0);
		while ((*str)[j] && ++k < filler->map->w)
		{
			if (!((*str)[j] == 'X' || (*str)[j] == 'x'
			|| (*str)[j] == 'o' || (*str)[j] == 'O' || (*str)[j] == '.'))
				return (0);
			filler->map->dmap[i][k] = get_heat_map_cell(filler, (*str)[j++]);
		}
		ft_strdel(str);
	}
	return (1);
}

int		set_piece(t_filler *filler, char **str, int i, int j)
{
	if (!(filler->piece->map =
	(char **)ft_memalloc(sizeof(char *) * (filler->piece->height + 1))))
		return (0);
	while ((j = 0) == 0
	&& ++i < filler->piece->height && get_next_line(MODE, str) > 0)
	{
		if (!(filler->piece->map[i] =
	(char *)ft_memalloc(sizeof(char) * (filler->piece->width + 1))))
			return (0);
		while ((*str)[j] && j < filler->piece->width)
		{
			if (!((*str)[j] == '.' || (*str)[j] == '*'))
				return (0);
			filler->piece->map[i][j] = (*str)[j];
			if ((*str)[j] == '*')
				calc_size(i, j, filler);
			j++;
		}
		ft_strdel(str);
	}
	return (1);
}

int		parse(t_filler *filler, char **str)
{
	if (!set_size(filler, 1, str))
		return (0);
	ft_strdel(str);
	if (get_next_line(MODE, str) <= 0)
		return (0);
	ft_strdel(str);
	if (!set_map(filler, str, -1, 0))
		return (0);
	ft_strdel(str);
	if (!set_size(filler, 0, str))
		return (0);
	ft_strdel(str);
	if (!set_piece(filler, str, -1, 0))
		ft_strdel(str);
	return (1);
}
