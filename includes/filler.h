/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:30:46 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/26 19:07:45 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H

# define FILLER_H
# define ERROR_CODE -10
# define EMPTY_CELL  -1
# define PLAYER_CELL -2
# define ENEMY_CELL -3
# define MAXINT	2147483647
# define MODE 0

# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef struct	s_map
{
	int			h;
	int			w;
	int			**dmap;
}				t_map;

typedef struct	s_piece
{
	char		**map;
	int			height;
	int			width;
	int			x_top_left;
	int			y_top_left;
	int			x_bottom_right;
	int			y_bottom_right;
	int			th;
	int			tw;
}				t_piece;

typedef struct	s_filler
{
	t_map		*map;
	t_piece		*piece;
	char		player;
	char		enemy;
	int			x;
	int			y;
}				t_filler;

t_filler		*init_filler();
void			filler_free(t_filler *filler);
void			heat_map_free(t_filler *filler);
void			place_piece(t_filler *filler, int i, int j);
int				mdist(t_filler *filler, int i, int j);
int				calc_piece_sum(t_filler *filler, int x, int y);
void			calc_size(int i, int j, t_filler *filler);
int				abs(int n);
int				parse(t_filler *filler, char **str);
#endif
