/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/04 19:57:41 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	reset_filler(t_filler *filler)
{
	filler->y = 0;
	filler->x = 0;
	filler->piece->height = 0;
	filler->piece->width = 0;
	filler->piece->x_bottom_right = 0;
	filler->piece->y_bottom_right = 0;
	filler->piece->x_top_left = MAXINT;
	filler->piece->y_top_left = MAXINT;
	filler->piece->th = 0;
	filler->piece->tw = 0;
	filler->map->w = 0;
	filler->map->h = 0;
	filler->map->dmap = 0;
	filler->piece->map = 0;
}

int		set_player(t_filler *filler, char **str)
{
	(*str) = 0;
	if (get_next_line(MODE, str) <= 0)
		return (0);
	if (ft_strlen((*str)) < 11)
	{
		ft_strdel(str);
		return (0);
	}
	filler->player = (*str)[10] == '1' ? 'o' : 'x';
	filler->enemy = filler->player == 'x' ? 'o' : 'x';
	ft_strdel(str);
	return (1);
}

void	clear_map(t_filler *filler)
{
	int	i;

	i = -1;
	while (filler->map->dmap && ++i < filler->map->h + 1)
		ft_memdel((void **)&(filler->map->dmap[i]));
	ft_memdel((void **)&(filler->map->dmap));
	i = -1;
	while (filler->piece->map && ++i < filler->piece->height + 1)
		ft_memdel((void **)&(filler->piece->map[i]));
	ft_memdel((void **)&(filler->piece->map));
}

void	print_answer(t_filler *filler)
{
	ft_putnbr(filler->y);
	ft_putchar(' ');
	ft_putnbr(filler->x);
	ft_putchar('\n');
}

int		main(void)
{
	t_filler	*filler;
	char		*str;

	str = 0;
	if ((filler = init_filler()) == 0)
		return (ERROR_CODE);
	reset_filler(filler);
	if (!set_player(filler, &str))
	{
		filler_free(filler);
		return (ERROR_CODE);
	}
	while (parse(filler, &str)
	&& !(filler->piece->y_top_left == MAXINT
	|| filler->piece->x_top_left == MAXINT))
	{
		place_piece(filler, 0, 0);
		print_answer(filler);
		ft_strdel(&str);
		clear_map(filler);
		reset_filler(filler);
	}
	clear_map(filler);
	ft_strdel(&str);
	filler_free(filler);
}
