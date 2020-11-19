
#include "../includes/assembler.h"


int 	parse_args(t_asm *asm_ctx, char *line, int *i)
{

	int		i1;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
		return (1);
	i1 = *i;
	while (line[i1] && line[i1] != COMMENT_CHAR && (line[i1] != ' ' || line[i1] != '\n'))
		++i1;
	while (get_next_arg(asm_ctx, line, i));
	skip_whitespaces(line, i);
	if (line[*i] && line[*i] != COMMENT_CHAR)
	{
		//handle error
		return (0);
	}
	if (!is_token_valid(asm_ctx, asm_ctx->last_token->content))
	{
		//handle error
		printf("token not valid\n");
		return (0);
	}
	((t_token *)(asm_ctx->last_token->content))->is_full = 1;
	//todo handle error
	return (1);
}

int 	parse_operation(t_asm *asm_ctx, char *line, int *i)
{
	int		i1;
	char	*op;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
		return (1);
	i1 = *i;
	while (line[i1] && line[i1] != COMMENT_CHAR && !is_space(line[i1]) && line[i1] != DIRECT_CHAR)
		++i1;
	op = ft_strsub(line, *i, i1 - *i);
	//printf("debug: %s\n", op);
	if (!set_operation(asm_ctx, op))
	{
		//todo handle error
		ft_strdel(&op);
		printf("temp error msg: %d, %d %s\n", *i, i1 - *i, op);
		return (0);
	}
	*i = i1;
	ft_strdel(&op);
	return (1);
}

int		parse_label(t_asm *asm_ctx, char *line, int *i)
{
	t_label	label;
	int		i1;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
		return (1);
	i1 = *i;
	while (line[i1] && line[i1] != COMMENT_CHAR && ft_strchr(LABEL_CHARS, line[i1]))
		++(i1);
	if (line[i1] == LABEL_CHAR)
	{
		label.name = ft_strsub(line, *i, i1 - *i);
		ft_lstadd(&((t_token *)(asm_ctx->last_token->content))->labels, ft_lstnew(&label, sizeof(label)));
		i1++;
		*i = i1;
		return (1);
	}
	return (0);
}

int		parse(t_asm *asm_ctx)
{
	char	*line;
	int		i;
	int     cur_position;

	cur_position = 0;
	while (get_next_line(asm_ctx->opened_fd, &line) > 0)
	{
		i = 0;
		skip_whitespaces(line, &i);
		if (ft_strlen(line) && (!(asm_ctx->last_token) || ((t_token *)(asm_ctx->last_token->content))->is_full))
			//TODO proper error handling
		{
			if (!create_token(asm_ctx, cur_position))
				return (0);
			((t_token *)(asm_ctx->last_token->content))->is_full = 0;
			cur_position++;
		}
		parse_label(asm_ctx, line, &i);
		skip_whitespaces(line, &i);
		parse_operation(asm_ctx, line, &i);
		skip_whitespaces(line, &i);
		parse_args(asm_ctx, line, &i);
		ft_strdel(&line);
	}
	return (1);
}