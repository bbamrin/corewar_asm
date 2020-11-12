
#include "../includes/assembler.h"


int 	parse_args(t_asm *asm_ctx, int *i)
{
	//TODO
}

int 	parse_command(t_asm *asm_ctx, int *i)
{
	//TODO
}

int		parse_label(t_asm *asm_ctx, int *i)
{
	//TODO
}

int		parse(t_asm *asm_ctx)
{
	char	*line;
	int		i;

	while (get_next_line(asm_ctx->opened_fd, &line) > 0)
	{
		//TODO add possibility to skip lines after labels, also think about skipping whitespaces in parse functions directly
		skip_whitespaces(line, &i);
		parse_label(asm_ctx, &i);
		parse_command(asm_ctx, &i);
		parse_args(asm_ctx, &i);
	}
}