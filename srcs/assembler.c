/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <pkathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/04 19:57:41 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"
#include <stdio.h>


void 	free_label(void *label_v, size_t label_size)
{
	t_label	*label;

	if (label_v)
	{
		label = (t_label *)label_v;
		ft_strdel(&label->name);
		ft_memdel((void **)&label);
		label_size += 1;
	}
}

void 	free_arg(void *arg_v, size_t arg_size)
{
	t_arg	*arg;

	if (arg_v)
	{
		arg = (t_arg *)arg_v;
		ft_strdel(&arg->value);
		ft_memdel((void **)&arg);
		arg_size += 1;
	}
}

void 	free_token(void *token_v, size_t token_size)
{
	t_token	*token;

	if (token_v)
	{
		token = (t_token *)token_v;
		if (token->args)
			ft_lstdel(&token->args, &free_arg);
		if (token->labels)
			ft_lstdel(&token->labels, &free_label);
		ft_memdel((void **)&token);
		token_size += 1;
	}
}


void 	free_asm(t_asm *asm_ctx)
{
	ft_strdel(&(asm_ctx->name));
	ft_strdel(&(asm_ctx->comment));
	if (asm_ctx->tokens)
		ft_lstdel(&asm_ctx->tokens, &free_token);
	ft_memdel((void **)&asm_ctx);
}

void	print_token(t_token *token)
{

	t_list  *label_l;
	t_label *label;
	t_list  *arg_l;
	t_arg   *arg;

		if (!token)
			return;
		printf("%d | ", get_token_size(token));
		label_l = token->labels;
		printf("%d: ", token->position);
		printf("| ");
		if (!label_l)
			printf("______ ");
		while (label_l)
		{
			label = (t_label *)(label_l->content);
			printf("%s ", label->name);
			label_l = label_l->next;
		}

		printf("| %s ",  token->operation.name);
		arg_l = token->args;
		printf("| ");
		while (arg_l)
		{
			arg = (t_arg *)arg_l->content;
			if (arg->type == T_IND)
				printf("T_IND ");
			else if (arg->type == T_DIR)
				printf("T_DIR ");
			else if (arg->type == T_REG)
				printf("T_REG ");
			else
				printf("error ");
			printf("%s ", arg->value);
			arg_l = arg_l->next;
		}
		printf("\n");
}

void    print_asm(t_asm *asm_ctx)
{
	t_list  *token_l;
	t_token *token;


	token_l = ((asm_ctx->tokens));
	while (token_l)
	{
		token = (t_token *)(token_l->content);
		if (!token)
			break;
		print_token(token);
		token_l = token_l->next;
	}
}

t_asm	*init()
{
	t_asm *asm_ctx;

	if (!(asm_ctx = ft_memalloc(sizeof(t_asm))))
		return (0);
	init_op_tab(asm_ctx);
	asm_ctx->name = ft_strdup("");
	asm_ctx->comment = ft_strdup("");
	asm_ctx->cmd_mode = -1;
	return (asm_ctx);
}

int		main(int argc, char **argv)
{
	t_asm	*asm_ctx;

	if (argc != 2)
	{
		printf("not enough files\n");
		return (0);
	}
	if (!(asm_ctx = init()))
	{
		printf("oops\n");
		return (0);
	}
	if (!(open_file(asm_ctx, argv[1])))
	{
		printf("cant open file\n");
		return (0);
	}
	int ret1 = get_cmd(asm_ctx);
	int ret2 = get_cmd(asm_ctx);
	printf("return: %d\nname: %s\n", ret1, asm_ctx->name);
	printf("return: %d\ncomment: %s\n", ret2, asm_ctx->comment);
	//add name and comment size checking
	//add handlind + before args
	parse(asm_ctx);
	if (!resolve_labels(asm_ctx))
		printf("error when resolving labels\n");
	print_asm(asm_ctx);
	free_asm(asm_ctx);
}
