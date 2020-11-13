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

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# define MAXINT	2147483647
# define MODE 0

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "op.h"


typedef struct	s_arg
{
	char		*type;
	void		*value;
}				t_arg;

typedef struct	s_label
{
	char		*name;
}				t_label;

typedef struct	s_token
{
	t_list		*labels;
	char		*operation;
	t_list		*args
	int			position;
}				t_token;

typedef struct	s_lexeme
{
	char	*this;
	char 	*next;
}				t_lexeme;

typedef struct s_asm
{
	t_list		*tokens;
	int			opened_fd;
}				t_asm;

int		skip_whitespaces(char *str, int *i);

#endif
