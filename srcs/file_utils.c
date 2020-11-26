
#include "../includes/assembler.h"

int		open_file(t_asm *asm_ctx, char *fname)
{
	int		fd;

	if ((fd = open(fname, O_RDONLY)) < 0)
		return (0);
	asm_ctx->opened_fd = fd;
	return (1);
}
