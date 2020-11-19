
#include "../includes/assembler.h"

int		set_operation(t_asm *asm_ctx, char *str)
{
	int	i;

	i = -1;
	while (++i < 17)
	{
		if (ft_strequ(str, asm_ctx->op_tab[i].name))
		{
			((t_token *)(asm_ctx->last_token->content))->operation = asm_ctx->op_tab[i];
			return (1);
		}
	}
	return (0);
}

int		get_next_arg(t_asm *asm_ctx, char *line, int *i)
{
	int		i1;
	t_arg	arg;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
	{
		arg.type = T_DIR;
		arg.value = ft_strdup("");
		ft_lstadd_end(&((t_token *)(asm_ctx->last_token->content))->args, ft_lstnew(&arg, sizeof(t_arg)));
		return (0);
	}
	skip_whitespaces(line, i);
	i1 = *i;
	if (line[*i] == DIRECT_CHAR)
	{
		arg.type = T_DIR;
		(*i)++;
	}
	else if (line[*i] == 'r')
		arg.type = T_REG;
	else
		arg.type = T_IND;
	while (line[i1] && line[i1] != COMMENT_CHAR && line[i1] != SEPARATOR_CHAR)
		++(i1);
	arg.value = ft_strsub(line, *i, i1  - *i);
	ft_lstadd_end(&((t_token *)(asm_ctx->last_token->content))->args, ft_lstnew(&arg, sizeof(t_arg)));
	if (line[i1] == SEPARATOR_CHAR)
		i1++;
	else
	{
		*i = i1;
		return (0);
	}
	*i = i1;
	return (1);
}

int		is_register_valid(char *val)
{
	int i;
	int reg_num;

	i = 0;

	if (!val[1])
		return (0);
	while (val[++i])
	{
		if(!(val[i] <= '9' && val[i] >= '0'))
			return (0);
	}
	reg_num = ft_atoi(&val[1]);
	if (reg_num > REG_NUMBER)
		return (0);
	return (1);
}

int		is_direct_valid(char *val)
{
	int i;

	if (val[0] == LABEL_CHAR)
	{
		i = 0;
		while (val[++i])
			if (!ft_strchr(LABEL_CHARS, val[i]))
				return (0);
	}
	else
	{
		i = -1;
		if (val[0] == '-')
			++i;
		while (val[++i])
			if(!(val[i] <= '9' && val[i] >= '0'))
				return (0);
	}
	return (1);
}

int		is_indirect_valid(char *val)
{
	int i;

	if (val[0] == LABEL_CHAR)
	{
		i = 0;
		while (val[++i])
			if (!ft_strchr(LABEL_CHARS, val[i]))
				return (0);
	}
	else
	{
		i = -1;
		if (val[0] == '-')
			++i;
		while (val[++i])
			if(!(val[i] <= '9' && val[i] >= '0'))
				return (0);
	}
	return (1);
}

int		is_arg_valid(t_arg *arg, int type)
{
	if (!(arg->type & type))
		return (0);
	if (arg->type == T_REG)
		return (is_register_valid(arg->value));
	else if (arg->type == T_DIR)
		return (is_direct_valid(arg->value));
	else if (arg->type == T_IND)
		return (is_indirect_valid(arg->value));
	//handle possible error
	return (0);
}

int		is_arg_list_valid(t_asm *asm_ctx, t_list *args, t_op operation)
{
	int	i;
	t_list *tmp;

	i = -1;
	tmp = args;
	while (tmp)
	{
		++i;
		if (i > operation.arg_count)
		{
			//handle error
			return (0);
		}
		if (!is_arg_valid((t_arg *)tmp->content, operation.arg_types[i]))
		{
			//handle error
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		is_token_valid(t_asm *asm_ctx, t_token *token)
{
	int i;

	i = -1;
	while ((asm_ctx->op_tab[++i]).name)
	{

		if (ft_strequ((token->operation).name, (asm_ctx->op_tab[i]).name))
			break;
	}
	if (!(asm_ctx->op_tab[i].name))
	{
		//handle error
		return (0);
	}
	if (!is_arg_list_valid(asm_ctx, token->args, asm_ctx->op_tab[i]))
	{
		printf("2\n");
		//handle error
		return (0);
	}
	return (1);
}

