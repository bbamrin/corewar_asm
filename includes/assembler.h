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
	t_op		operation;
	t_list		*args;
	int			position;
	int			line_num;
	int         is_full;
}				t_token;

typedef struct s_asm
{
	t_op			op_tab[17];
	t_list			*tokens;
	t_list			*last_token;
	char			*name;
	char			*comment;
	unsigned char	*champ_code;
	int				opened_fd;
	int 			cmd_mode;
	int 			champ_code_size;
	int 			was_comment;
	int 			was_name;
	int 			is_little_endian;
	int 			line_count;
	char 			*out_name;
}				t_asm;

int		skip_whitespaces(char *str, int *i);
int		is_space(char c);
void	ft_lstadd_end(t_list **alst, t_list *new);
int		create_token(t_asm *asm_ctx, int position);
int		parse(t_asm *asm_ctx, int cur_position);
int		open_file(t_asm *asm_ctx, char *fname);
int		set_operation(t_asm *asm_ctx, char *str);
void	init_op_tab(t_asm *asm_ctx);
int		get_next_arg(t_asm *asm_ctx, char *line, int *i);
void	is_token_valid(t_asm *asm_ctx, t_token *token);
int		get_cmd(t_asm *asm_ctx);
int		get_token_size(t_token *token);
int 	clean_trim(char **str_res, char *to_trim);
int		resolve_labels(t_asm *asm_ctx);
void	print_token(t_token *token);
int		assemble(t_asm *asm_ctx);
int 	set_header_command(t_asm *asm_ctx);
void 	throw_error(t_asm *asm_ctx, const char *msg1, const char *msg2);
void 	throw_line_error(t_asm *asm_ctx, const char *msg1, const char *msg2, int line_num);

#endif
