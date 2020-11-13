
#include "../includes/assembler.h"


int 	parse_args(t_asm *asm_ctx, char *line, int *i)
{
	//TODO
}

int 	parse_command(t_asm *asm_ctx, char *line, int *i)
{
	//TODO
}

int		parse_label(t_asm *asm_ctx, char *line, int *i)
{
	t_label	label;
	int		i1;

	i1 = *i;
	while (line[i1] && ft_strchr(LABEL_CHARS, line[i1]))
		++(i1);
	if (line[i1] == LABEL_CHAR)
	{
		label.name = ft_strsub(line, 0, i1);
		ft_lstadd(&((t_token *)(asm_ctx->tokens->content))->labels, ft_lstnew(&label, sizeof(label)));
		return (1);
	}
	return (0);
}

int		parse(t_asm *asm_ctx)
{
	char	*line;
	int		i;

	while (get_next_line(asm_ctx->opened_fd, &line) > 0)
	{
		//TODO add possibility to skip lines after labels, also think about skipping whitespaces in parse functions directly
		skip_whitespaces(line, &i);
		parse_label(asm_ctx, line, &i);
		parse_command(asm_ctx, line, &i);
		parse_args(asm_ctx, line, &i);
	}
}