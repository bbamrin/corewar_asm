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
	int			type;
	char        *value;
}				t_arg;

typedef struct	s_label
{
	char		*name;
}				t_label;

typedef struct	s_token
{
	t_list		*labels;
	//static
	t_op		operation;
	t_list		*args;
	int			position;
	int         is_full;
}				t_token;

typedef struct s_asm
{
	t_op		op_tab[17];
	t_list		*tokens;
	t_list		*last_token;
	char		*name;
	char		*comment;
	int			opened_fd;
	int 		cmd_mode;
}				t_asm;

int		skip_whitespaces(char *str, int *i);
int		is_space(char c);
void	ft_lstadd_end(t_list **alst, t_list *new);
int		create_token(t_asm *asm_ctx, int position);
int		parse(t_asm *asm_ctx);
int		open_file(t_asm *asm_ctx, char *fname);
int		set_operation(t_asm *asm_ctx, char *str);
void	init_op_tab(t_asm *asm_ctx);
int		get_next_arg(t_asm *asm_ctx, char *line, int *i);
int		is_token_valid(t_asm *asm_ctx, t_token *token);
int		get_cmd(t_asm *asm_ctx);

#endif
