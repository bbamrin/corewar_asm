
#include "../includes/assembler.h"

int		get_token_size(t_token *token)
{
	int size;
	t_list *temp;

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
		{

			size += ft_strstr("lfork lldi fork sti ldi zjmp",  token->operation.name) ? 2 : 4;
		}

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

int		convert_label(t_asm *asm_ctx, t_arg *arg, t_list *token)
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
		return (0);
	if(!(dist = ft_itoa(get_distance(token, end_token))))
		return (0);
	ft_strdel(&arg->value);
	arg->value = dist;
	return (1);
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
			&& ((t_arg *)(start_arg->content))->value[0] == LABEL_CHAR
			&& !convert_label(asm_ctx, (t_arg *)(start_arg->content), start_token))
			{
				printf("error in position %d\n", ((t_token *)(start_token->content))->position);
				return (0);
			}

			start_arg = start_arg->next;
		}
		start_token = start_token->next;
	}
	return (1);
}


int 	assemble(t_asm *asm_ctx)
{
	return (0);
}