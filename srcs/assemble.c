
#include "../includes/assembler.h"

int		get_dir_size(t_op operation)
{
	if (ft_strequ(operation.name, "lfork") ||
			ft_strequ(operation.name, "lldi") ||
			ft_strequ(operation.name, "fork") ||
			ft_strequ(operation.name, "sti") ||
			ft_strequ(operation.name, "ldi") ||
			ft_strequ(operation.name, "zjmp"))
		return (2);
	else
		return (4);
}

int		get_token_size(t_token *token)
{
	int		size;
	t_list	*temp;

	if (!(token->operation.name))
		return (0);
	size = 1;
	if (token->operation.is_arg_type_code)
		size++;
	if (!token->args)
		return (size);
	temp = token->args;
	while (temp)
	{
		if (((t_arg *)temp->content)->type == T_IND)
			size += IND_SIZE;
		else if (((t_arg *)temp->content)->type == T_DIR)
			size += get_dir_size(token->operation);
		else if (((t_arg *)temp->content)->type == T_REG)
			size += 1;
		temp = temp->next;
	}
	return (size);
}

int 	get_distance(t_list *node1, t_list *node2)
{
	t_list	*start;
	t_list	*end;
	int 	result;
	int 	sign;

	result = 0;
	if (((t_token *)(node1->content))->position > ((t_token *)(node2->content))->position)
	{
		start = node2;
		end = node1;
		sign = -1;
	}
	else
	{
		start = node1;
		end = node2;
		sign = 1;
	}
	while (start && ((t_token *)(start->content))->position != ((t_token *)(end->content))->position)
	{
		result += get_token_size(((t_token *)(start->content)));
		start = start->next;
	}
	return (result * sign);
}

void	convert_label(t_asm *asm_ctx, t_arg *arg, t_list *token)
{
	t_list	*start_token;
	t_list	*start_label;
	t_list	*end_token;
	char 	*dist;

	start_token = asm_ctx->tokens;
	end_token = 0;
	while (start_token)
	{
		start_label = ((t_token *)(start_token->content))->labels;
		while (start_label)
		{
			if (ft_strequ(((t_label *)(start_label->content))->name, arg->value + 1))
				end_token = start_token;
			start_label = start_label->next;
		}
		start_token = start_token->next;
	}
	if (!end_token)
		throw_line_error(asm_ctx, "wrong label", arg->value + 1, ((t_token *)(token->content))->line_num);
	if(!(dist = ft_itoa(get_distance(token, end_token))))
		throw_error(asm_ctx, "malloc error", 0);
	ft_strdel(&arg->value);
	arg->value = dist;
}

int 	resolve_labels(t_asm *asm_ctx)
{
	t_list	*start_token;
	t_list	*start_arg;

	start_token = asm_ctx->tokens;
	while (start_token)
	{
		start_arg = ((t_token *)(start_token->content))->args;
		while (start_arg)
		{
			if (((t_arg *)(start_arg->content))->value
			&& ((t_arg *)(start_arg->content))->value[0] == LABEL_CHAR)
				convert_label(asm_ctx, (t_arg *)(start_arg->content), start_token);
			start_arg = start_arg->next;
		}
		start_token = start_token->next;
	}
	return (1);
}

int 			set_champ_code_size(t_asm *asm_ctx)
{
	int size;

	size = get_distance(asm_ctx->tokens, asm_ctx->last_token);
	size += get_token_size((t_token *)(asm_ctx->last_token->content));
	asm_ctx->champ_code_size = size;
	return (1);
}

int 	get_big_endian_int(int n)
{
	int	res;

	res = ((n >> 24) & 0xff) | ((n >> 16) & 0xff) << 8 | ((n >> 8) & 0xff) << 16 | (n & 0xff) << 24;
	return (res);
}

void	set_byte_code(t_asm *asm_ctx, int data, int size, int *i)
{
	unsigned char *data_tmp;

	if (asm_ctx->is_little_endian)
		data = get_big_endian_int(data);
	data_tmp = (unsigned  char *)&data;
	data_tmp += sizeof(int) - size;
	while (size-- > 0)
	{
		asm_ctx->champ_code[*i] = *data_tmp;
		data_tmp++;
		(*i)++;
	}
}

int 	set_args_byte_code(t_asm *asm_ctx, t_list *arg_l, int dir_size, int *i)
{
	t_arg	*arg;
	int 	type_code;
	int 	offset;
	int 	data;

	offset = 6;
	type_code = 0;
	while (arg_l)
	{
		arg = (t_arg *)arg_l->content;
		type_code |= (arg->type == T_IND ? 3 : arg->type) << offset;
		if (arg->value[0] == 'r')
			data = ft_atoi(arg->value + 1);
		else
			data = ft_atoi(arg->value);
		offset -= 2;
		if (arg->type == T_IND)
			set_byte_code(asm_ctx, data, 2, i);
		else if (arg->type == T_DIR)
			set_byte_code(asm_ctx, data, dir_size, i);
		else if (arg->type == T_REG)
			set_byte_code(asm_ctx, data,1, i);
		arg_l = arg_l->next;
	}
	return (type_code);
}

int		set_token_byte_code(t_asm *asm_ctx, t_token *token, int *i)
{
	int		arg_type;
	int		arg_type_idx;

	arg_type = 0;
	if (!(token->operation.name))
		return (0);
	asm_ctx->champ_code[*i] = token->operation.id;
	*i += 1;
	if (token->operation.is_arg_type_code)
	{
		arg_type_idx = *i;
		(*i)++;
	}
	arg_type = set_args_byte_code(asm_ctx, token->args, get_dir_size(token->operation), i);
	if (token->operation.is_arg_type_code)
		asm_ctx->champ_code[arg_type_idx] = arg_type;
	return (1);
}

int		set_champ_byte_code(t_asm *asm_ctx)
{
	int i;
	t_list *token_l;

	i = 0;
	set_champ_code_size(asm_ctx);
	if (!(asm_ctx->champ_code
	= (unsigned char *)ft_memalloc(asm_ctx->champ_code_size)))
		return (0);
	token_l = asm_ctx->tokens;
	while (token_l)
	{
		set_token_byte_code(asm_ctx, (t_token *)(token_l->content), &i);
		token_l = token_l->next;
	}
	return (1);
}

int 	create_champ(t_asm *asm_ctx)
{
	int fd;
	int magic;

	fd = open ("test.cor", O_WRONLY|O_TRUNC|O_CREAT);
	if (fd < 0)
		return (0);
	magic = COREWAR_EXEC_MAGIC;
	magic = get_big_endian_int(magic);
	write(fd, &magic, 4);
	write(fd, asm_ctx->name, PROG_NAME_LENGTH);
	magic = 0;
	write(fd, &magic, 4);
	magic = get_big_endian_int(asm_ctx->champ_code_size);
	write(fd, &(magic), 4);
	magic = 0;
	write(fd, asm_ctx->comment, COMMENT_LENGTH);
	write(fd, &magic, 4);
	write(fd, asm_ctx->champ_code, asm_ctx->champ_code_size);
	close(fd);
	return (1);
}

int 	assemble(t_asm *asm_ctx)
{
	set_champ_byte_code(asm_ctx);
	if (!create_champ(asm_ctx))
		return (0);
	return (1);
}