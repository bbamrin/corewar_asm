
#include "../includes/assembler.h"

int 	concat_cmd(t_asm *asm_ctx, char *line, int start, int len)
{
	char	*tmp;
	char	*tmp1;
	char 	*result;

	if (!(tmp = ft_strsub(line, start, len)))
		return (0);
	tmp1 = asm_ctx->cmd_mode ? asm_ctx->comment : asm_ctx->name;
	if (!(result = ft_strjoin(tmp1, tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	if (asm_ctx->cmd_mode == 1)
		asm_ctx->comment = result;
	else if (asm_ctx->cmd_mode == 0)
		asm_ctx->name = result;
	ft_strdel(&tmp1);
	ft_strdel(&tmp);
	return (1);
}

int 	read_cmd(t_asm *asm_ctx, char *line)
{
	int i;
	char *sep;

	if (!line[0])
	{
		concat_cmd(asm_ctx, "\n", 0, 1);
		return (1);
	}
	i = 0;
	if ((sep = ft_strchr(line, '"')))
	{
		i = sep - line + 1;
		if (!concat_cmd(asm_ctx, line, 0, sep - line))
			return (-1);
		skip_whitespaces(line, &i);
		if (line[i] && line[i] != COMMENT_CHAR)
			return (-1);
		return (0);
	}
	if (!concat_cmd(asm_ctx, line, 0, ft_strlen(line))
	|| !concat_cmd(asm_ctx, "\n", 0, 1))
		return (-1);
	return (1);
}

void 	set_cmd_mode(t_asm *asm_ctx, char *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		asm_ctx->cmd_mode = 0;
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		asm_ctx->cmd_mode = 1;
	else
		asm_ctx->cmd_mode = -1;
}

int 	skip_header_void(t_asm *asm_ctx, char **line, int *i)
{
	int ret;

	while ((ret = get_next_line(asm_ctx->opened_fd, line)) > 0)
	{
		*i = 0;
		skip_whitespaces(*line, i);
		//printf("%s i: %d\n", *line, *i);
		if ((*line)[*i] && (*line)[*i] != COMMENT_CHAR)
		{
			//printf("debug\n");
			//printf("%s\n", *line);
			return (1);
		}

		else
			ft_strdel(line);
	}
	printf("debug\n");
	return (ret);
}

int		get_cmd(t_asm *asm_ctx)
{
	int		i;
	int 	ret;
	char	*line;

	i = 0;
	if ((ret = skip_header_void(asm_ctx, &line, &i)) <= 0)
		return (ret);
	//skip_whitespaces(line, &i);
	set_cmd_mode(asm_ctx, &line[i]);
	//printf("%s\n", line);
	if (asm_ctx->cmd_mode == -1)
		return (-1);
	i += ft_strlen(asm_ctx->cmd_mode ? COMMENT_CMD_STRING : NAME_CMD_STRING);
	skip_whitespaces(line, &i);
	if (line[i++] != '"')
		return (-1);
	ret = read_cmd(asm_ctx, &line[i]);
	ft_strdel(&line);
	if (ret <= 0)
		return (ret);
	while (get_next_line(asm_ctx->opened_fd, &line)
	&& (ret = read_cmd(asm_ctx, line)) == 1)
		ft_strdel(&line);
	ft_strdel(&line);
	return (ret);
}
